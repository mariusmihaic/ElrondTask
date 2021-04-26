#pragma warning(disable:4996)
#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include "../../Utils/ext.h"
#include "../PemHandler/pemhandler.h"
#include "sodium.h"


namespace ih
{
  class JsonHandler : public IFileHandler
  {
    uint64_t invalidRet = 0;

  public:
    explicit JsonHandler(std::map<uint32_t, std::string> userInputs):
      IFileHandler(userInputs[ARGS_TX_IDX_JSON_OUT_FILE]),
      m_userInputs(userInputs),
      m_pemHandler(userInputs[ARGS_TX_IDX_PEM_INPUT_FILE])
    {
      m_signWithData = (userInputs.find(ARGS_TX_IDX_DATA) != userInputs.end())
        ? (true) : (false);
    }
    //TODO: handle if pem/json input is not path
    bool isFileValid() override
    {
      return fileExists() && isFileExtensionValid("json");
    }

    void writeOutputFile();

  private:

    uint64_t getNonce();
    std::string getValue();
    std::string getReceiver();
    std::string getSender();
    uint64_t getGasPrice();
    uint64_t getGasLimit();
    std::string getData();
    std::string getChainId();
    uint64_t getVersion();
    std::string getInputFile()
    {
      return m_userInputs[ARGS_TX_IDX_PEM_INPUT_FILE];
    }
    std::string getOutputFile();

    nlohmann::ordered_json createUnsignedTransaction();

    void signTransaction(nlohmann::ordered_json& transaction);

    std::string getJsonSerialized();

    std::string getSignature(nlohmann::ordered_json unsignedTransaction);

    std::map<uint32_t, std::string> m_userInputs;
    ih::PemFileHandler m_pemHandler;
    bool m_signWithData;
  };
}

#endif