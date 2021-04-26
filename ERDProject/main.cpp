#include <sodium.h>
#include <string>
#include <iostream>
#include <vector>
#include "..\InputHandler\ext.h"

int main(int argc, char* argv[])
{
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
    ih::PemFileHandler pemHandler(argHandler.getPemFilePath());

    if (pemHandler.isFileValid())
    {
    }
    else
    {
      argHandler.reportError(ERROR_PEM_INPUT_FILE);
    }
    break;
  }
  case ih::createTransactionNoData:
  {
    ih::JsonHandler jsonHandler(reqestedCmd.getUserInputs());

    if (jsonHandler.isFileValid())
    {
    }
    else
    {
      argHandler.reportError(ERROR_JSON_OUT_FILE);
    }

    break;
  }
  case ih::createTransactionWithData:
  {
    std::cerr << "Create trans WITH data";
    break;
  }
  default:
  {
    argHandler.showInfo();
  }
  }


  if (sodium_init() < 0) {
    /* panic! the library couldn't be initialized, it is not safe to use */
  }

  //std::string privateAndPublicKey = "MWY0ZGQ4YjdkMThiNWQwNzg1YzlkMDgwMmVjMTRkNTUzZGJhMzU2ODEyYjg1YzdlMzQxNDM3MzM4ODQ3MjAxMDg0YTE2OGNkNGQ3ZDg2MDg4NDg2MzJkMDk3ODNkMjhhZTlhODIzOTAwNzc5Mjk1NjY3NTdlMjU1OTZmZTk2NDc";

  //crypto_sign_ed25519_sk_to_pk(pkERD, skERD);

  return 0;
}