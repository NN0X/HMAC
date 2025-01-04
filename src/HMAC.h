#ifndef HMAC_H
#define HMAC_H

#include <vector>
#include <cstdint>

namespace HMAC
{
        std::vector<uint8_t> hmacSHA512(std::vector<uint8_t> key, std::vector<uint8_t> message, std::vector<uint8_t> (*hashFunc)(const std::vector<uint8_t> &), size_t blockSize);
}

#endif
