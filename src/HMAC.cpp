#include <vector>
#include <cstdint>

#include "HMAC.h"

std::vector<uint8_t> HMACns::hmac(std::vector<uint8_t> key, std::vector<uint8_t> message, unsigned char *(*hashFunc)(const unsigned char *, size_t, unsigned char *nullPass), size_t blockSize, size_t outputSize)
{
        if (hashFunc == nullptr)
        {
                return std::vector<uint8_t>();
        }


        if (key.size() > blockSize)
        {
                unsigned char *keyPtr = hashFunc(key.data(), key.size(), NULL);
                key = std::vector<uint8_t>(keyPtr, keyPtr + outputSize);
        }

        if (key.size() < blockSize)
        {
                key.resize(blockSize, 0x00);
        }

        std::vector<uint8_t> opad(blockSize, 0x5c);
        std::vector<uint8_t> ipad(blockSize, 0x36);

        for (size_t i = 0; i < blockSize; i++)
        {
                opad[i] ^= key[i];
                ipad[i] ^= key[i];
        }

        ipad.reserve(ipad.size() + message.size());
        for (uint8_t byte : message)
        {
                ipad.push_back(byte);
        }

        unsigned char *ipadHash = hashFunc(ipad.data(), ipad.size(), NULL);

        opad.reserve(opad.size() + outputSize);
        for (size_t i = 0; i < outputSize; i++)
        {
                opad.push_back(ipadHash[i]);
        }
        unsigned char *opadHash = hashFunc(opad.data(), opad.size(), NULL);

        return std::vector<uint8_t>(opadHash, opadHash + outputSize);
}
