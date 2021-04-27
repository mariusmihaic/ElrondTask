#ifndef IFILEHANDLER_H
#define IFILEHANDLER_H

#include <string>
#include <fstream>

namespace ih
{
  class IFileHandler
  {
  public:
    IFileHandler(std::string const& path) : m_filePath(path)
    {}

    virtual bool isFileValid() const
    {
      return fileExists();
    }

    const std::string &getFilePath() const
    {
      return m_filePath;
    }
  protected:

    bool fileExists() const
    {
      std::ifstream f(m_filePath);
      return f.good() && f.is_open();
    }

    bool isFileExtensionValid(std::string const ext) const
    {
      return getFileExtension() == ext;
    }


  private:
    std::string getFileExtension() const
    {
      std::string ext = "";

      if (m_filePath.find_last_of(".") != std::string::npos)
        ext = m_filePath.substr(m_filePath.find_last_of(".") + 1);

      return ext;
    }

    std::string m_filePath;

  };
}
#endif
