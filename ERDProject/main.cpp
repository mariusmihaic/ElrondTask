#include <sodium.h>
#include <string>
#include <iostream>
#include <vector>
#include "..\InputHandler\ext.h"

int main(int argc, char* argv[])
{
  ih::ArgHandler argHandler(argc, argv);
  ih::ArgHandler::RequestedCmd reqestedCmd = argHandler.getRequestedCmd();

  switch (reqestedCmd)
  {
  case ih::ArgHandler::help:
  {
    argHandler.showInfo();
  }
  case ih::ArgHandler::loadPemFile:
  {
    ih::PemFileHandler pemHandler(argHandler.getPemFilePath());
    if (pemHandler.isFileValid())
    {
    }
    break;
  }
  case ih::ArgHandler::createTransactionNoData:
  {
    std::cerr << "Create trans no data";
    break;
  }
  case ih::ArgHandler::createTransactionWithData:
  {
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