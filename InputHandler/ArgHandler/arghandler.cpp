#include "arghandler.h"
#include <iostream>

namespace ih
{
  ArgHandler::commandGroupMap const ArgHandler::m_commandGroupMap =
  {
    {{"transaction"} , {"new"}},
    {"pem" , {"load"}},
    {"help" , {}}
  };

  //TODO: This should be changed. should only look at first params to be subcomands, not inside all m_arguments
  bool ArgHandler::isSubCommandGroup(std::string const subCommandGroup) const
  {
    if (argCount() <= 1) return false;
    return (std::find(m_arguments.begin() + 1, m_arguments.end(), subCommandGroup) != m_arguments.end());
  }

  bool ArgHandler::isCommandGroup(std::string const arg) const
  {
    if (argCount() == 0) return false;
    return (m_arguments[0] == arg);
  }

  template<typename T>
  bool ArgHandler::isUserInputValid(std::string arg) const
  {
    if ((arg.size() == 0) || (arg.size() > std::numeric_limits<uint64_t>::digits)) return false;

    std::string::const_iterator it = arg.begin();
    while (it != arg.end() && isdigit(*it)) ++it;
    return  it == arg.end();
  }

  template<>
  bool ArgHandler::isUserInputValid<std::string>(std::string arg) const
  {
    return (arg.size() != 0);
  }

  template <typename T>
  bool ArgHandler::checkAndSetUserInput(unsigned int const argIdx, std::string const arg,
                                        std::map<uint32_t, std::string>& userInputs, uint32_t valIdx,
                                        errorCode errCode)
  {
    // If user didn't provide enough arguments OR
    // size(user arg) <= size(required arg)
    if (argCount() <= argIdx) return false;
    if (m_arguments[argIdx].size() <= arg.size()) return false;

    bool ret = false;

    std::string const userArg = m_arguments[argIdx];
    std::string const userCmd = userArg.substr(0, arg.size());
    bool const isCmdValid = (userCmd == arg) ? (true) : (false);

    if (isCmdValid)
    {
      std::string const userInput = userArg.substr(arg.size(), userArg.size());
      if (isUserInputValid<T>(userInput))
      {
        userInputs[valIdx] = userInput;
        ret = true;
      }
      else
      {
        m_errCode &= errCode;
      }
    }

    return ret;
  }

  std::string ArgHandler::getPemFilePath() const
  {
    std::string ret = "";
    if (argCount() == 3) ret =  m_arguments[2];
    return ret;
  }

  RequestedCmd ArgHandler::getRequestedCmd()
  {
    m_errCode = ERROR_NONE;
    RequestType reqType = invalid;
    std::map<uint32_t, std::string> userInputs;

    // TODO: No magic numbers
    if ((argCount() == 1) && isCommandGroup("help"))
    {
      reqType = help;
    }
    else if ((argCount() == 3) && isCommandGroup("pem") && isSubCommandGroup("load") &&
             (checkAndSetUserInput<std::string>(2U, "--file=", userInputs, ARGS_PEM_IDX_FILE, ERROR_PEM_INPUT_FILE)))
    {
      reqType = loadPemFile;
    }
    else if (((argCount() == 10) || (argCount() == 9)) && isCommandGroup("transaction") && isSubCommandGroup("new") &&
      checkAndSetUserInput<uint64_t>(2U, "--nonce=", userInputs, ARGS_TX_IDX_NONCE, ERROR_NONCE) &&
      checkAndSetUserInput<std::string>(3U, "--value=", userInputs, ARGS_TX_IDX_VALUE, ERROR_VALUE) &&
      checkAndSetUserInput<std::string>(4U, "--receiver=", userInputs, ARGS_TX_IDX_RECEIVER, ERROR_RECEIVER) &&
      checkAndSetUserInput<uint64_t>(5U, "--gas-price=", userInputs, ARGS_TX_IDX_GAS_PRICE, ERROR_GAS_PRICE) &&
      checkAndSetUserInput<uint64_t>(6U, "--gas-limit=", userInputs, ARGS_TX_IDX_GAS_LIMIT, ERROR_GAS_LIMIT) &&
      checkAndSetUserInput<std::string>(7U, "--pem=", userInputs, ARGS_TX_IDX_PEM_INPUT_FILE, ERROR_PEM_INPUT_FILE) &&
      checkAndSetUserInput<std::string>(8U, "--outfile=", userInputs, ARGS_TX_IDX_JSON_OUT_FILE, ERROR_JSON_OUT_FILE))
    {
      if (argCount() == 9)
      {
        reqType = createTransactionNoData;
      }
      else if ((argCount() == 10) &&
        checkAndSetUserInput<std::string>(8U, "--data=", userInputs, ARGS_TX_IDX_DATA, ERROR_DATA))
      {
        reqType = createTransactionWithData;
      }
    }

    return RequestedCmd(userInputs, reqType ,m_errCode);
  }

  int ArgHandler::argCount() const
  {
    return m_arguments.size();
  }

  bool ArgHandler::areArgumentsValid()
  {
    if (m_arguments.size() == 0)
    {
      return false;
    }

    bool argumentsValid = false;

    std::string const argumentGroup = m_arguments[0];

    auto itGroup = ArgHandler::m_commandGroupMap.find(argumentGroup);

    if (itGroup != m_commandGroupMap.end())
    {
      std::vector<std::string> subGroup = itGroup->second;

      for (unsigned int ct = 1; ct < m_arguments.size(); ++ct)
      {
        if (std::find(subGroup.begin(), subGroup.end(), m_arguments[ct]) != subGroup.end())
        {
          argumentsValid = true;
        }
      }
    }
    return argumentsValid;
  }

  void ArgHandler::showSubGroupAvailableCmds(std::string cmdGroup) const
  {
    std::vector<std::string> cmds = m_commandGroupMap.at(cmdGroup);

    if (cmds.size() == 0) std::cerr << "-";
    else
    {
      for (std::string cmd : cmds)
      {
        std::cerr << cmd << " ";
      }
    }
  }

  void ArgHandler::reportError(errorCode const err) const
  {
    std::cerr << errors.at(err);
  }

  void ArgHandler::showInfo() const
  {
    std::cerr << "----\nInfo\n----\n\nCommand groups: Avaiable arguments\n";

    for (auto it = m_commandGroupMap.begin(); it != m_commandGroupMap.end(); ++it)
    {
      std::cerr << it->first << ": ";
      showSubGroupAvailableCmds(it->first);
      std::cerr << "\n";
    }
  }
}
