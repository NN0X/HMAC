#include <iostream>
#include <cstring>

#include <openssl/sha.h>

#include "tests.h"
#include "HMAC.h"

#define DEFAULT_HASH SHA512
#define DEFAULT_EVP EVP_sha512()
#define DEFAULT_BLOCK My::SHA512_BLOCK
#define DEFAULT_OUT My::SHA512_OUT

int main(int argc, char *argv[])
{
        unsigned char *(*sha)(const unsigned char *, size_t, unsigned char *nullPass) = nullptr;
        const EVP_MD *evpSHA = nullptr;
        size_t blockSize = 0;
        size_t outputSize = 0;

        if (argc == 2)
        {
                std::string arg(argv[1]);
                if (arg == "help")
                {
                        std::cout << "Usage: " << argv[0] << " <key> <message>\n";
                        std::cout << "Usage: " << argv[0] << " <key> <message> <hash function>\n";
                        std::cout << "Usage: " << argv[0] << " test <n> <hash function>\n";
                        std::cout << "Usage: " << argv[0] << " test <message> -o\n";
                        std::cout << "Usage: " << argv[0] << " test <message> <hash function> -o\n";
                        std::cout << "\t-o --override\tOverride test keyword\n";
                        std::cout << "Supported hashing algorithms: SHA1, SHA256, SHA512\n";
                        return 2;
                }
        }

        if (argc != 3 && argc != 4 && argc != 5)
        {
                std::cout << "Usage: " << argv[0] << " <key> <message>\n";
                std::cout << "Usage: " << argv[0] << " <key> <message> <hash function>\n";
                std::cout << "Usage: " << argv[0] << " test <n> <hash function>\n";
                return 1;
        }

        bool override = false;
        if (argc == 4)
        {
                std::string hashFunc(argv[3]);
                if (hashFunc == "SHA1")
                {
                        sha = SHA1;
                        evpSHA = EVP_sha1();
                        blockSize = My::SHA1_BLOCK;
                        outputSize = My::SHA1_OUT;
                }
                else if (hashFunc == "SHA256")
                {
                        sha = SHA256;
                        evpSHA = EVP_sha256();
                        blockSize = My::SHA256_BLOCK;
                        outputSize = My::SHA256_OUT;
                }
                else if (hashFunc == "SHA512")
                {
                        sha = SHA512;
                        evpSHA = EVP_sha512();
                        blockSize = My::SHA512_BLOCK;
                        outputSize = My::SHA512_OUT;
                }
                else if (hashFunc == "-o" || hashFunc == "--override")
                {
                        override = true;
                        sha = DEFAULT_HASH;
                        evpSHA = DEFAULT_EVP;
                        blockSize = DEFAULT_BLOCK;
                        outputSize = DEFAULT_OUT;
                }
                else
                {
                        std::cout << "Invalid hash function\n";
                        return 3;
                }
        }
        else
        {
                sha = DEFAULT_HASH;
                evpSHA = DEFAULT_EVP;
                blockSize = DEFAULT_BLOCK;
                outputSize = DEFAULT_OUT;
        }

        if (argc == 5)
        {
                std::string arg(argv[4]);
                if (arg == "-o" || arg == "--override")
                {
                        override = true;
                }
        }

        std::string arg(argv[1]);
        if (arg == "test" && !override)
        {
                try
                {
                        int n = std::stoi(argv[2]);
                        testRandomPairs(n, sha, evpSHA, blockSize, outputSize);
                        return 0;
                }
                catch (std::invalid_argument &e)
                {
                        std::cout << "Invalid number of tests\n";
                        return 4;
                }
        }


        std::vector<uint8_t> keyBytes(argv[1], argv[1] + strlen(argv[1]));
        std::vector<uint8_t> messageBytes(argv[2], argv[2] + strlen(argv[2]));

        std::vector<uint8_t> hashed = My::hmac(keyBytes, messageBytes, sha, blockSize, outputSize);

        for (uint8_t byte : hashed)
        {
                std::cout << std::hex << (int)byte;
        }

        return 0;
}
