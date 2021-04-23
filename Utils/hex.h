#ifndef HEX_H
#define HEX_H

#include <string>
#include <vector>

namespace util
{
  inline std::vector<char> hexToBytes(const std::string& hex)
  {
    std::vector<char> bytes;

    for (unsigned int i = 0; i < hex.length(); i += 2) {
      std::string byteString = hex.substr(i, 2);
      char byte = (char)strtol(byteString.c_str(), NULL, 16);
      bytes.push_back(byte);
    }

    return bytes;
  }
}

#endif