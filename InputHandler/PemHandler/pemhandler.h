#ifndef PEMHANDLER_H
#define PEMHANDLER_H

#include <string>
#include <vector>
#include "../IFileHandler/IFileHandler.h"

namespace ih
{
  class PemFileHandler : public IFileHandler
  {
    std::string const hrp = "erd";

  public:
    explicit PemFileHandler(std::string const& path):
      IFileHandler(path)
    {
      m_fileContent = getFileContent();
    }

    bool isFileValid() override;

    void getSeed(unsigned char* seed) const;

    void getPublicKey(unsigned char* pk) const;

    void getPrivateKey(unsigned char* pk) const;

    std::string getSegwitAddress() const;

  private:

    std::string getFileContent() const;

    std::vector<char> getKeyBytesFromFile() const;

    std::string m_fileContent;
  };
}

#endif