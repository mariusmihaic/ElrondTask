#ifndef ARGHANDLER_H
#define ARGHANDLER_H

#include <string>
#include <vector>
#include <map>
#include "../../Utils/params.h"

namespace ih
{
  enum RequestType
  {
    invalid,
    help,
    loadPemFile,
    createTransaction
  };

  class RequestedCmd
  {
  public:
    RequestedCmd(std::map<uint32_t, std::string> const userInputs,
                 RequestType const reqType, errorCode const errCode);

    const std::map<uint32_t, std::string>& getUserInputs() const;

    const RequestType& getRequestType() const;

    const errorCode& getErrorCode() const;

  private:
    std::map<uint32_t, std::string> const m_userInputs;
    RequestType const m_requestType;
    errorCode const m_errCode;
  };

  class ArgHandler
  {
    typedef std::map<std::string, std::vector<std::string>> commandGroupMap;

  public:

    explicit ArgHandler(int const& argc, char* const argv[]);

    RequestedCmd getRequestedCmd();

    void reportError(errorCode err) const;

    void showInfo() const;

  private:

    int argCount() const;

    bool isCmdGroup(std::string const arg) const;

    bool isSubCmd(uint32_t const subCmdIdx, std::string const subCmd) const;

    template <typename T>
    bool checkAndSetUserInput(uint32_t const argIdx, std::string const arg,
                              std::map<uint32_t,std::string>& userInputs, uint32_t valIdx,
                              errorCode errCode);

    // Generic template function to check for user input value.
    // Expects input to be an unsigned long int.
    template<typename T>
    bool isUserInputValid(std::string arg) const;

    // Specialization template function to check for user input value.
    // Expects input to be a non-empty string.
    template<>
    bool isUserInputValid<std::string>(std::string arg) const;

    void showSubGroupAvailableCmds(std::string cmdGroup) const;

    std::vector <std::string> m_arguments;
    errorCode m_errCode;
    static commandGroupMap const m_commandGroupMap;
  };
}



#endif // !ARGHANDLER_H