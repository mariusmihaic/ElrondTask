#ifndef STRINGTOCHAR_H
#define STRINGTOCHAR_H

#include <string>
#include <vector>

namespace util
{
  inline std::string uCharToStr(unsigned char* chrBuffer, unsigned int const bufferSize)
  {
    std::string ret;

    for (auto currChar = 0; currChar < bufferSize; ++currChar)
    {
      ret.push_back(chrBuffer[currChar]);
    }

    return ret;
  }
}

#endif