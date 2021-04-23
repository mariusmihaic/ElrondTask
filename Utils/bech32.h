#ifndef BECH32_H
#define BECH32_H

#include <string>
#include <vector>
#include <stdint.h>

namespace util
{
  namespace bech32
  {
    /** encode a Bech32 string. Returns the empty string in case of failure. */
    std::string encode(const std::string& hrp, const std::vector<uint8_t>& values);

    /** decode a Bech32 string. Returns (hrp, data). Empty hrp means failure. */
    std::pair<std::string, std::vector<uint8_t>> decode(const std::string& str);
  }
}

#endif