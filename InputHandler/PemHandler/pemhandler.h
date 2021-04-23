#ifndef PEMHANDLER_H
#define PEMHANDLER_H

#include <string>
#include <vector>

namespace ih
{
  class PemFileHandler
  {
    std::string const hrp = "erd";

  public:
    explicit PemFileHandler(std::string const& path):
      m_filePath(path)
    {
      m_fileContent = getFileContent();
    }

    bool isFileValid() const;

    void getSeed(unsigned char* seed) const;

    void getPublicKey(unsigned char* pk) const;

    void getPrivateKey(unsigned char* pk) const;

    std::string getSegwitAddress() const;

  private:

    bool isFileExtensionValid() const;

    std::string getFileContent() const;

    std::string getFileExtension() const;

    std::vector<char> getKeyBytesFromFile() const;


    std::string m_fileContent;
    std::string m_filePath;
  };
}

#endif