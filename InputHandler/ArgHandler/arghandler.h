#ifndef ARGHANDLER_H
#define ARGHANDLER_H

#include <string>
#include <vector>
#include <map>
#include "../../Utils/params.h"

namespace ih
{
  // TODO: Add here an error code as well for return or as input param for argHandler
  enum RequestType
  {
    invalid,
    help,
    loadPemFile,
    createTransactionWithData,
    createTransactionNoData,
  };

  class RequestedCmd
  {
  public:
    RequestedCmd(std::map<uint32_t,std::string> const userInputs,
                 RequestType const reqType, errorCode const errCode) :
      m_userInputs(userInputs), m_requestType(reqType), m_errCode(errCode){}

    const std::map<uint32_t, std::string>& getUserInputs() const
    {
      return m_userInputs;
    }
    const RequestType& getRequestType() const
    {
      return m_requestType;
    }
    const errorCode& getErrorCode() const
    {
      return m_errCode;
    }

  private:
    std::map<uint32_t, std::string> const m_userInputs;
    RequestType const m_requestType;
    errorCode const m_errCode;
  };

  class ArgHandler
  {
  public:

    explicit ArgHandler(int const& argc, char* const argv[]) : m_errCode(ERROR_NONE)
    {
      if (argc > 1)
      {
        for (int ct = 1; ct < argc; ++ct)
        {
          m_arguments.push_back(std::string(argv[ct]));
        }
      }
    }

    RequestedCmd getRequestedCmd();

    std::string getPemFilePath() const;

    void reportError(errorCode const err) const;

    void showInfo() const;

  private:

    int argCount() const;

    bool isCommandGroup(std::string const arg) const;

    bool isSubCommandGroup(std::string const subCommandGroup) const;

    template <typename T>
    bool checkAndSetUserInput(unsigned int const argIdx,
                              std::string const arg, std::map<uint32_t,std::string>& userInputs,
                              uint32_t valIdx, errorCode errCode);

    // Generic template function to check for user value input.
    // Expects input to be an unsigned long int.
    template<typename T>
    bool isUserInputValid(std::string arg) const;

    // Specialization template function to check for user value input.
    // Expects input to be a non-empty string.
    template<>
    bool isUserInputValid<std::string>(std::string arg) const;

    void showSubGroupAvailableCmds(std::string cmdGroup) const;

    bool areArgumentsValid();

    typedef std::map<std::string, std::vector<std::string>> commandGroupMap;
    std::vector <std::string> m_arguments;
    errorCode m_errCode;
    static commandGroupMap const m_commandGroupMap;
  };
}



#endif // !ARGHANDLER_H