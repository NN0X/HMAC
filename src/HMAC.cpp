#include <iostream>
#include <vector>
#include <cstdint>

#include "HMAC.h"
#include "SHA512.h"

std::vector<uint8_t> HMAC::hmacSHA512(std::vector<uint8_t> key, std::vector<uint8_t> message, std::vector<uint8_t> (*hashFunc)(const std::vector<uint8_t> &), size_t blockSize)
{
        if (key.size() > blockSize)
        {
                key = hashFunc(key);
        }

        if (key.size() < blockSize)
        {
                key.resize(blockSize, 0x00);
        }

        std::vector<uint8_t> opad(blockSize, 0x5c);
        std::vector<uint8_t> ipad(blockSize, 0x36);

        for (size_t i = 0; i < key.size(); i++)
        {
                opad[i] ^= key[i];
                ipad[i] ^= key[i];
        }

        std::vector<uint8_t> innerBytes = ipad;
        innerBytes.insert(innerBytes.end(), message.begin(), message.end());

        std::vector<uint8_t> innerHash = hashFunc(innerBytes);

        std::vector<uint8_t> outerBytes = opad;
        outerBytes.insert(outerBytes.end(), innerHash.begin(), innerHash.end());

        return hashFunc(outerBytes);
}
