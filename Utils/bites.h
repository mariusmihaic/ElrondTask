#ifndef BITES_H
#define BITES_H

#include <vector>

namespace util
{
  std::vector<uint8_t> convertBits(unsigned char* data, unsigned int const dataLength ,
                                   int const fromBits, int const toBits, bool const pad);
}
#endif