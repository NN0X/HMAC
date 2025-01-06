#ifndef HMAC_H
#define HMAC_H

#include <vector>
#include <cstdint>

namespace My
{
        enum BlockSize
        {
                SHA1_BLOCK = 64,
                SHA256_BLOCK = 64,
                SHA512_BLOCK = 128
        };

        enum OutputSize
        {
                SHA1_OUT = 20,
                SHA256_OUT = 32,
                SHA512_OUT = 64
        };


        std::vector<uint8_t> hmac(std::vector<uint8_t> key, std::vector<uint8_t> message, unsigned char *(*hashFunc)(const unsigned char *, size_t, unsigned char *nullPass), size_t blockSize, size_t outputSize);
}

#endif
