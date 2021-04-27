#include <sodium.h>
#include <string>
#include <iostream>
#include <vector>
#include "..\InputHandler\ext.h"

int main(int argc, char* argv[])
{
  if (sodium_init() < 0)
  {
    /* panic! the library couldn't be initialized, it is not safe to use */
  }

  ih::ArgHandler argHandler(argc, argv);

  ih::RequestedCmd const reqestedCmd = argHandler.getRequestedCmd();
  errorCode const errCode = reqestedCmd.getErrorCode();

  if (errCode != ERROR_NONE)
  {
    argHandler.reportError(errCode);
    return 0;
  }

  ih::RequestType const reqType = reqestedCmd.getRequestType();

  switch (reqType)
  {
  case ih::help:
  {
    argHandler.showInfo();
  }
  case ih::loadPemFile:
  {
    ih::wrapper::PemHandlerInputWrapper const pemInputWrapper(reqestedCmd.getUserInputs());
    ih::PemFileHandler pemHandler(pemInputWrapper);

    if (pemHandler.isFileValid())
    {
      pemHandler.printFileContent();
    }
    else
    {
      argHandler.reportError(ERROR_PEM_INPUT_FILE);
    }
    break;
  }
  case ih::createTransaction:
  {
    ih::wrapper::PemHandlerInputWrapper const pemInputWrapper(reqestedCmd.getUserInputs());
    ih::wrapper::JsonHandlerInputWrapper const jsonInputWrapper(reqestedCmd.getUserInputs());
    ih::JsonHandler jsonHandler(pemInputWrapper , jsonInputWrapper);

    if (jsonHandler.isFileValid())
    {
      jsonHandler.writeOutputFile();
    }
    else
    {
      argHandler.reportError(ERROR_JSON_OUT_FILE);
    }

    break;
  }
  default:
  {
    argHandler.showInfo();
  }
  }

  return 0;
}