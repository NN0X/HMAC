#ifndef HMAC_H
#define HMAC_H

#include <vector>
#include <cstdint>

namespace HMACns
{
        std::vector<uint8_t> hmac(std::vector<uint8_t> key, std::vector<uint8_t> message, unsigned char *(*hashFunc)(const unsigned char *, size_t, unsigned char *nullPass), size_t blockSize, size_t outputSize);
}

#endif
