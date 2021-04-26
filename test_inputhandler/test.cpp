#include "pch.h"

TEST(ArgHandler, getRequestedCmd_noArgument)
{
  int const argc = 1;
  char* argv[argc];
  argv[0] = "ERDProject.exe";

  ih::ArgHandler argHandler(argc, argv);

  EXPECT_EQ(argHandler.getRequestedCmd().getRequestType(), ih::invalid);
}

TEST(ArgHandler, getRequestedCmd_randomArgs)
{
  int const argc = 3;
  char* argv[argc];
  argv[0] = "ERDProject.exe";
  argv[1] = "dsa";
  argv[2] = "";

  ih::ArgHandler argHandler(argc, argv);

  EXPECT_EQ(argHandler.getRequestedCmd().getRequestType(), ih::invalid);
}

TEST(ArgHandler, getRequestedCmd_help)
{
  int const argc = 2;
  char* argv[argc];
  argv[0] = "ERDProject.exe";
  argv[1] = "help";

  ih::ArgHandler argHandler(argc, argv);

  EXPECT_EQ(argHandler.getRequestedCmd().getRequestType(), ih::help);
}

TEST(ArgHandler, getRequestedCmd_pem_load_someFile)
{
  int const argc = 4;
  char* argv[argc];
  argv[0] = "ERDProject.exe";
  argv[1] = "pem";
  argv[2] = "load";
  argv[3] = "--file=someFile";

  ih::ArgHandler argHandler(argc, argv);

  EXPECT_EQ(argHandler.getRequestedCmd().getRequestType(), ih::loadPemFile);
}

TEST(ArgHandler, getRequestedCmd_pem_help)
{
  int const argc = 3;
  char* argv[argc];
  argv[0] = "ERDProject.exe";
  argv[1] = "pem";
  argv[2] = "help";

  ih::ArgHandler argHandler(argc, argv);

  EXPECT_EQ(argHandler.getRequestedCmd().getRequestType(), ih::invalid);
}

TEST(ArgHandler, getRequestedCmd_pem_withoutSubArgument)
{
  int const argc = 2;
  char* argv[argc];
  argv[0] = "ERDProject.exe";
  argv[1] = "pem";

  ih::ArgHandler argHandler(argc, argv);

  EXPECT_EQ(argHandler.getRequestedCmd().getRequestType(), ih::invalid);
}

TEST(ArgHandler, getRequestedCmd_transaction_new_noData)
{
  int const argc = 9;
  char* argv[argc];
  argv[0] = "ERDProject.exe";
  argv[1] = "transaction";
  argv[2] = "new";
  argv[3] = "--nonce=3";
  argv[4] = "--value=\"31\"";
  argv[5] = "--receiver=\"da\"";
  argv[6] = "--gas-price=31";
  argv[7] = "--gas-limit=31";
  argv[8] = "--outfile=\"dd\"";

  ih::ArgHandler argHandler(argc, argv);

  EXPECT_EQ(argHandler.getRequestedCmd().getRequestType(), ih::createTransactionNoData);
}

TEST(ArgHandler, getRequestedCmd_transaction_new_withData)
{
  int const argc = 10;
  char* argv[argc];
  argv[0] = "ERDProject.exe";
  argv[1] = "transaction";
  argv[2] = "new";
  argv[3] = "--nonce=3";
  argv[4] = "--value=\"31\"";
  argv[5] = "--receiver=\"da\"";
  argv[6] = "--gas-price=31";
  argv[7] = "--gas-limit=31";
  argv[8] = "--outfile=\"dd\"";
  argv[9] = "--data=\"dd\"";

  ih::ArgHandler argHandler(argc, argv);

  EXPECT_EQ(argHandler.getRequestedCmd().getRequestType(), ih::createTransactionWithData);
}

TEST(JsonHandler, writeOutputFile)
{
  std::map<uint32_t, std::string> input;

  input[ARGS_TX_IDX_NONCE] = "3";
  input[ARGS_TX_IDX_VALUE] = "444";
  input[ARGS_TX_IDX_RECEIVER] = "addr";
  input[ARGS_TX_IDX_GAS_PRICE] = "111";
  input[ARGS_TX_IDX_GAS_LIMIT] = "111";
  input[ARGS_TX_IDX_DATA] = "data";
  input[ARGS_TX_IDX_PEM_INPUT_FILE] = "D:/ERD/ERDProject/testData/keys.pem";
  input[ARGS_TX_IDX_JSON_OUT_FILE] = "D:/ERD/ERDProject/testData/outputJson.json";

  ih::JsonHandler jsonHandler(input);

  jsonHandler.writeOutputFile();
}





TEST(ArgHandler, getPemFilePath_someFile)
{
  int const argc = 4;
  char* argv[argc];
  argv[0] = "ERDProject.exe";
  argv[1] = "pem";
  argv[2] = "-load";
  argv[3] = "someFile";

  ih::ArgHandler argHandler(argc, argv);

  EXPECT_EQ(argHandler.getPemFilePath(), argv[3]);
}

TEST(ArgHandler, getPemFilePath_invalidArguments_emptyPath)
{
  int const argc = 5;
  char* argv[argc];
  argv[0] = "ERDProject.exe";
  argv[1] = "pem";
  argv[2] = "-load";
  argv[3] = "someFile";
  argv[4] = "someExtraArgument";

  ih::ArgHandler argHandler(argc, argv);

  EXPECT_EQ(argHandler.getPemFilePath(), "");
}


TEST(PemFileReader, isPemFileValid_validFile)
{
  ih::PemFileHandler pemHandler("D:/ERD/libsodium/ERDProject/testData/keys.pem");

  EXPECT_TRUE(pemHandler.isFileValid());
}

TEST(PemFileReader, isPemFileValid_invalidFileExtension)
{
  ih::PemFileHandler pemHandler("D:/ERD/libsodium/ERDProject/testData/keys.pme");

  EXPECT_FALSE(pemHandler.isFileValid());
}

TEST(PemFileReader, isPemFileValid_emptyFile)
{
  ih::PemFileHandler pemHandler("D:/ERD/libsodium/ERDProject/testData/keysEmptyFile.pem");

  EXPECT_FALSE(pemHandler.isFileValid());
}

TEST(PemFileReader, getPublicPrivateKeys_expectSameResultFrom_libsodium)
{
  ih::PemFileHandler pemHandler("D:/ERD/libsodium/ERDProject/testData/keys.pem");

  unsigned char pemPk[crypto_sign_PUBLICKEYBYTES];
  unsigned char pemSk[crypto_sign_SECRETKEYBYTES];
  unsigned char pemSeed[crypto_sign_SEEDBYTES];

  unsigned char sodiumPk[crypto_sign_PUBLICKEYBYTES];
  unsigned char sodiumSk[crypto_sign_SECRETKEYBYTES];

  pemHandler.getSeed(pemSeed);
  pemHandler.getPublicKey(pemPk);
  pemHandler.getPrivateKey(pemSk);

  crypto_sign_seed_keypair(sodiumPk, sodiumSk, pemSeed);

  for (int currByte = 0; currByte < crypto_sign_PUBLICKEYBYTES; currByte++)
  {
    EXPECT_EQ(sodiumPk[currByte], pemPk[currByte]);
  }

  for (int currByte = 0; currByte < crypto_sign_SECRETKEYBYTES; currByte++)
  {
    EXPECT_EQ(sodiumSk[currByte], pemSk[currByte]);
  }
}

TEST(PemFileReader, getSegwitAddress)
{
  ih::PemFileHandler pemHandler("D:/ERD/libsodium/ERDProject/testData/keys.pem");

  std::string pemAddress = pemHandler.getSegwitAddress();
  std::string expectedAdr = "erd1sjsk3n2d0krq3pyxxtgf0q7j3t56sgusqaujj4n82l39t9h7jers6gslr4";

  EXPECT_EQ(pemAddress, expectedAdr);
}

