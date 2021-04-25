#ifndef ARGHANDLER_H
#define ARGHANDLER_H

#include <string>
#include <vector>
#include <map>

namespace ih
{
  class ArgHandler
  {
  public:
    // TODO: Add here an error code as well for return or as input param for argHandler
    enum RequestedCmd
    {
      invalid,
      help,
      loadPemFile,
      createTransactionWithData,
      createTransactionNoData,
      signTransaction
    };

    explicit ArgHandler(int const& argc, char* const argv[])
    {
      if (argc > 1)
      {
        for (int ct = 1; ct < argc; ++ct)
        {
          m_arguments.push_back(std::string(argv[ct]));
        }
      }
    }

    RequestedCmd getRequestedCmd() const;

    std::string getPemFilePath() const;

    void showInfo() const;

  private:

    int argCount() const;

    bool isCommandGroup(std::string const arg) const;

    bool isSubCommandGroup(std::string const subCommandGroup) const;

    template <typename T>
    bool isArgumentValid(unsigned int const idx, std::string const arg) const;

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
    static commandGroupMap const m_commandGroupMap;
  };
}



#endif // !ARGHANDLER_H