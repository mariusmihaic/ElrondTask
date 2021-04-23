#include "pch.h"

TEST(ArgHandler, getRequestedCmd_noArgument)
{
  int const argc = 1;
  char* argv[argc];
  argv[0] = "ERDProject.exe";

  ih::ArgHandler argHandler(argc, argv);

  EXPECT_EQ(argHandler.getRequestedCmd(), ih::ArgHandler::invalid);
}

TEST(ArgHandler, getRequestedCmd_randomArgs)
{
  int const argc = 3;
  char* argv[argc];
  argv[0] = "ERDProject.exe";
  argv[1] = "dsa";
  argv[2] = "";

  ih::ArgHandler argHandler(argc, argv);

  EXPECT_EQ(argHandler.getRequestedCmd(), ih::ArgHandler::invalid);
}

TEST(ArgHandler, getRequestedCmd_help)
{
  int const argc = 2;
  char* argv[argc];
  argv[0] = "ERDProject.exe";
  argv[1] = "help";

  ih::ArgHandler argHandler(argc, argv);

  EXPECT_EQ(argHandler.getRequestedCmd(), ih::ArgHandler::help);
}

TEST(ArgHandler, getRequestedCmd_pem_load_someFile)
{
  int const argc = 4;
  char* argv[argc];
  argv[0] = "ERDProject.exe";
  argv[1] = "pem";
  argv[2] = "-load";
  argv[3] = "someFile";

  ih::ArgHandler argHandler(argc, argv);

  EXPECT_EQ(argHandler.getRequestedCmd(), ih::ArgHandler::loadPemFile);
}

TEST(ArgHandler, getRequestedCmd_pem_help)
{
  int const argc = 3;
  char* argv[argc];
  argv[0] = "ERDProject.exe";
  argv[1] = "pem";
  argv[2] = "help";

  ih::ArgHandler argHandler(argc, argv);

  EXPECT_EQ(argHandler.getRequestedCmd(), ih::ArgHandler::invalid);
}

TEST(ArgHandler, getRequestedCmd_pem_withoutSubArgument)
{
  int const argc = 2;
  char* argv[argc];
  argv[0] = "ERDProject.exe";
  argv[1] = "pem";

  ih::ArgHandler argHandler(argc, argv);

  EXPECT_EQ(argHandler.getRequestedCmd(), ih::ArgHandler::invalid);
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