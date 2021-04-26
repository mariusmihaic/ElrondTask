#ifndef HEX_H
#define HEX_H

#include <string>
#include <vector>

namespace util
{
  std::vector<char> hexToBytes(const std::string& hex);

  std::string stringToHex(const std::string& input);

  std::string hexToString(const std::string& input);
}

#endif