#include "IFileHandler.h"

namespace ih
{
  IFileHandler::IFileHandler(std::string const& path) :
    m_filePath(path){}

  bool IFileHandler::isFileValid() const
  {
    return fileExists();
  }

  const std::string &IFileHandler::getFilePath() const
  {
    return m_filePath;
  }

  bool IFileHandler::fileExists() const
  {
    std::ifstream f(m_filePath);
    return f.good() && f.is_open();
  }

  bool IFileHandler::isFileExtensionValid(std::string const ext) const
  {
    return getFileExtension() == ext;
  }

  std::string IFileHandler::getFileExtension() const
  {
    std::string ext = "";

    if (m_filePath.find_last_of(".") != std::string::npos)
      ext = m_filePath.substr(m_filePath.find_last_of(".") + 1);

    return ext;
  }

}
