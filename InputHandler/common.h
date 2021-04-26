#ifndef COMMON_ARGHANDLR_H
#define COMMON_ARGHANDLR_H

#include <string>
#include <fstream>

namespace common
{
  bool fileExists(std::string const file)
  {
    std::ifstream f(file);
    return f.good() && f.is_open();
  }

  std::string getFileExtension(std::string file)
  {
    std::string ext = "";

    if (file.find_last_of(".") != std::string::npos)
      ext = file.substr(file.find_last_of(".") + 1);

    return ext;
  }

  bool isFileExtensionValid(std::string const file, std::string const ext)
  {
    return getFileExtension(file) == ext;
  }

}

#endif