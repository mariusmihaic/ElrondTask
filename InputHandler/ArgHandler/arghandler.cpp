#include "arghandler.h"
#include <iostream>

namespace ih
{
  ArgHandler::commandGroupMap const ArgHandler::m_commandGroupMap =
  {
    {"pem" , {"-load"}},
    {"help" , {}}
  };

  bool ArgHandler::isSubCommandGroup(std::string subCommandGroup) const
  {
    if (argCount() <= 1) return false;
    return (std::find(m_arguments.begin() + 1, m_arguments.end(), subCommandGroup) != m_arguments.end());
  }

  bool ArgHandler::isCommandGroup(std::string arg) const
  {
    if (argCount() == 0) return false;
    return (m_arguments[0] == arg);
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

    if ((argCount() == 3) && isCommandGroup("pem") && isSubCommandGroup("-load")) ret = loadPemFile;
    else if ((argCount() == 1) && isCommandGroup("help")) ret = help;

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
