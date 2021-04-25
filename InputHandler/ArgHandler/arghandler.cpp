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
  bool ArgHandler::isArgumentValid(unsigned int const idx, std::string const arg) const
  {
    // If user didn't provide enough arguments OR
    // size(user arg) <= size(required arg)
    if (argCount() <= idx) return false;
    if (m_arguments[idx].size() <= arg.size()) return false;

    bool ret = false;
    std::string const userArg = m_arguments[idx];
    bool const isCmdValid = (userArg.substr(0, arg.size()) == arg) ? (true) : (false);

    if (isCmdValid)
    {
      std::string userInput = userArg.substr(arg.size(), userArg.size());
      ret = isUserInputValid<T>(userInput);
    }

    return ret;
  }

  std::string ArgHandler::getPemFilePath() const
  {
    std::string ret = "";
    if (argCount() == 3) ret =  m_arguments[2];
    return ret;
  }

  ArgHandler::RequestedCmd ArgHandler::getRequestedCmd() const
  {
    RequestedCmd ret = invalid;
    // TODO: No magic numbers

    if ((argCount() == 1) && isCommandGroup("help"))
    {
      ret = help;
    }
    else if ((argCount() == 3) && isCommandGroup("pem") && isSubCommandGroup("load"))
    {
      ret = loadPemFile;
    }
    else if (((argCount() == 9) || (argCount() == 8)) && isCommandGroup("transaction") && isSubCommandGroup("new") &&
      isArgumentValid<uint64_t>(2U, "--nonce=") &&
      isArgumentValid<std::string>(3U, "--value=") &&
      isArgumentValid<std::string>(4U, "--receiver=") &&
      isArgumentValid<uint64_t>(5U, "--gas-price=") &&
      isArgumentValid<uint64_t>(6U, "--gas-limit=") &&
      isArgumentValid<std::string>(7U, "--outfile="))
    {
      if (argCount() == 8)
      {
        ret = createTransactionNoData;
      }
      else if ((argCount() == 9) && isArgumentValid<std::string>(8U, "--data="))
      {
        ret = createTransactionWithData;
      }
    }


    return ret;
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
