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
    enum RequestedCmd
    {
      invalid,
      help,
      loadPemFile
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

    bool isSubCommandGroup(std::string subCommandGroup) const;

    bool isCommandGroup(std::string arg) const;

    void showSubGroupAvailableCmds(std::string cmdGroup) const;

    bool areArgumentsValid();

    typedef std::map<std::string, std::vector<std::string>> commandGroupMap;
    std::vector <std::string> m_arguments;
    static commandGroupMap const m_commandGroupMap;
  };
}



#endif // !ARGHANDLER_H