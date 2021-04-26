#include "jsonhandler.h"

namespace ih
{
  void JsonHandler::writeOutputFile()
  {
    std::ofstream myfile(getOutputFile());

    if (myfile.is_open())
    {
      nlohmann::ordered_json transaction = createUnsignedTransaction();
      signTransaction(transaction);
      myfile << transaction.dump();
      myfile.close();
    }
    else std::cerr << "Unable to open file";
  }

  nlohmann::ordered_json JsonHandler::createUnsignedTransaction()
  {
    nlohmann::ordered_json json;

    json[STR_JSON_NONCE] = getNonce();
    json[STR_JSON_VALUE] = getValue();
    json[STR_JSON_RECEIVER] = getReceiver();
    json[STR_JSON_SENDER] = getSender();
    json[STR_JSON_GAS_PRICE] = getGasPrice();
    json[STR_JSON_GAS_LIMIT] = getGasLimit();
    if (m_signWithData)
    {
      json[STR_JSON_DATA] = getData();
    }
    json[STR_JSON_CHAIN_ID] = getChainId();
    json[STR_JSON_VERSION] = getVersion();

    return json;
  }

  void JsonHandler::signTransaction(nlohmann::ordered_json& transaction)
  {
    transaction[STR_JSON_SIGNATURE] = getSignature(transaction);
  }

  std::string JsonHandler::getSignature(nlohmann::ordered_json unsignedTransaction)
  {
    std::string const msgString = unsignedTransaction.dump();
    unsigned long long const msgLength = msgString.length();

    unsigned char *msg = new unsigned char[msgLength + 1];
    std::strcpy((char*)msg, msgString.c_str());

    unsigned char sk[crypto_sign_SECRETKEYBYTES];
    unsigned char sig[crypto_sign_BYTES];

    m_pemHandler.getPrivateKey(sk);

    crypto_sign_detached(sig, NULL, msg, msgLength, sk);
    std::string ret = util::uCharToStr(sig, crypto_sign_BYTES);

    delete msg;
    return util::stringToHex(ret);
  }

  uint64_t JsonHandler::getNonce()
  {
    uint64_t ret = invalidRet;
    try
    {
      ret = std::stoul(m_userInputs[ARGS_TX_IDX_NONCE]);
      throw ERROR_INVALID_NONCE;
    }
    catch (uint32_t ERROR_INVALID_NONCE)
    {
      //TODO: ADD HERE TO ERROR.
    }
    return ret;
  }

  std::string JsonHandler::getValue()
  {
    return m_userInputs[ARGS_TX_IDX_VALUE];
  }

  std::string JsonHandler::getReceiver()
  {
    return m_userInputs[ARGS_TX_IDX_RECEIVER];
  }

  uint64_t JsonHandler::getGasPrice()
  {
    uint64_t ret = invalidRet;
    try
    {
      ret = std::stoul(m_userInputs[ARGS_TX_IDX_GAS_PRICE]);
      throw ERROR_INVALID_NONCE;
    }
    catch (uint32_t ERROR_INVALID_GAS_PRICE)
    {
      //TODO: ADD HERE TO ERROR.
    }
    return ret;
  }

  uint64_t JsonHandler::getGasLimit()
  {
    uint64_t ret = invalidRet;
    try
    {
      ret = std::stoul(m_userInputs[ARGS_TX_IDX_GAS_LIMIT]);
      throw ERROR_INVALID_NONCE;
    }
    catch (uint32_t ERROR_INVALID_GAS_LIMIT)
    {
      //TODO: ADD HERE TO ERROR.
    }
    return ret;
  }

  std::string JsonHandler::getData()
  {
    return m_userInputs[ARGS_TX_IDX_DATA];
  }

  std::string JsonHandler::getChainId()
  {
    return JSON_TX_DEFAULT_CHAIN_ID;;
  }

  uint64_t JsonHandler::getVersion()
  {
    return JSON_TX_DEFAULT_VERSION;
  }

  std::string JsonHandler::getOutputFile()
  {
    return m_userInputs[ARGS_TX_IDX_JSON_OUT_FILE];
  }

  std::string JsonHandler::getSender()
  {
    std::string pemFilePath = m_userInputs[ARGS_TX_IDX_PEM_INPUT_FILE];
    ih::PemFileHandler pemHandler(pemFilePath);
    return (pemHandler.isFileValid()) ? (pemHandler.getSegwitAddress()) : ("");
  }

  std::string JsonHandler::getJsonSerialized()
  {
    nlohmann::ordered_json json;


    //TODO: Check here if all passed without errors, then continue, not otherwise
    return json.dump();
  }
}

