#include <vector>
#include <cstdint>

#include "HMAC.h"

const uint8_t ZERO = 0x00;
const uint8_t IPAD = 0x36;
const uint8_t OPAD = 0x5c;

std::vector<uint8_t> My::hmac(std::vector<uint8_t> key, std::vector<uint8_t> message, unsigned char *(*hashFunc)(const unsigned char *, size_t, unsigned char *nullPass), size_t blockSize, size_t outputSize)
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
                key.resize(blockSize, ZERO);
        }

        std::vector<uint8_t> opad(blockSize, OPAD);
        std::vector<uint8_t> ipad(blockSize, IPAD);

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
