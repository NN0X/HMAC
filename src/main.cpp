#include <iostream>
#include <cstring>

#include <openssl/sha.h>
#include <openssl/hmac.h>

#include "HMAC.h"
#include "tests.h"

int main(int argc, char *argv[])
{
        unsigned char *(*sha)(const unsigned char *, size_t, unsigned char *nullPass) = nullptr;
        const EVP_MD *evpSHA = nullptr;
        size_t blockSize = 0;
        size_t outputSize = 0;

        if (argc == 2 && strcmp(argv[1], "help") == 0)
        {
                std::cout << "Usage: " << argv[0] << " <key> <message>\n";
                std::cout << "Usage: " << argv[0] << " <key> <message> <hash function>\n";
                std::cout << "Usage: " << argv[0] << " test <n> <hash function>\n";
                std::cout << "hash function: SHA1, SHA256, SHA512\n";
                return 2;
        }

        if (argc != 3 && argc != 4)
        {
                std::cout << "Usage: " << argv[0] << " <key> <message>\n";
                std::cout << "Usage: " << argv[0] << " <key> <message> <hash function>\n";
                std::cout << "Usage: " << argv[0] << " test <n> <hash function>\n";
                return 1;
        }

        if (argc == 4)
        {
                std::string hashFunc(argv[3]);
                if (hashFunc == "SHA1")
                {
                        sha = SHA1;
                        evpSHA = EVP_sha1();
                        blockSize = 64;
                        outputSize = 20;
                }
                else if (hashFunc == "SHA256")
                {
                        sha = SHA256;
                        evpSHA = EVP_sha256();
                        blockSize = 64;
                        outputSize = 32;
                }
                else if (hashFunc == "SHA512")
                {
                        sha = SHA512;
                        evpSHA = EVP_sha512();
                        blockSize = 128;
                        outputSize = 64;
                }
                else
                {
                        std::cout << "Invalid hash function\n";
                        return 3;
                }
        }
        else
        {
                sha = SHA512;
                evpSHA = EVP_sha512();
                blockSize = 128;
                outputSize = 64;
        }

        if (strcmp(argv[1], "test") == 0)
        {
                int n = std::stoi(argv[2]);
                testRandomPairs(n, sha, evpSHA, blockSize, outputSize);
                return 0;
        }


        std::vector<uint8_t> keyBytes(argv[1], argv[1] + strlen(argv[1]));
        std::vector<uint8_t> messageBytes(argv[2], argv[2] + strlen(argv[2]));

        std::vector<uint8_t> hashed = HMACns::hmac(keyBytes, messageBytes, sha, blockSize, outputSize);

        for (uint8_t byte : hashed)
        {
                std::cout << std::hex << (int)byte;
        }

        return 0;
}
