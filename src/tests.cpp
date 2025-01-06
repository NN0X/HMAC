#include <iostream>
#include <vector>
#include <cstdint>
#include <random>
#include <algorithm>

#include <openssl/hmac.h>

#include "HMAC.h"

const uint8_t ZERO = 0x00;
const uint8_t MAX_BYTE = 0xFF;
const int MAX_LEN = 1024;

bool testHMAC(const std::vector<uint8_t> &key, const std::vector<uint8_t> &message, const std::vector<uint8_t> &got, const EVP_MD *md, size_t outputSize)
{
        std::vector<uint8_t> expected(outputSize);

        unsigned char *expectedPtr = HMAC(md, key.data(), key.size(), message.data(), message.size(), NULL, NULL);
        std::copy(expectedPtr, expectedPtr + outputSize, expected.begin());

        return std::equal(expected.begin(), expected.end(), got.begin());
}

std::vector<uint8_t> genRandomBytes(int minLen, int maxLen, int n)
{
        std::vector<uint8_t> bytes(n);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(minLen, maxLen);

        for (int i = 0; i < n; i++)
        {
                bytes[i] = dis(gen);
        }

        return bytes;
}

void testRandomPairs(int n, unsigned char *(*hashFunc)(const unsigned char *, size_t, unsigned char *nullPass), const EVP_MD *md, size_t blockSize, size_t outputSize)
{
        bool verbose = false;
        std::cout << "Print verbose output? (Y/n): ";
        char c;
        std::cin >> c;
        if (c == 'Y' || c == 'y')
        {
                verbose = true;
        }

        int passed = 0;
        for (int i = 0; i < n; i++)
        {
                std::vector<uint8_t> key = genRandomBytes(ZERO, MAX_BYTE, MAX_LEN);
                std::vector<uint8_t> message = genRandomBytes(ZERO, MAX_BYTE, MAX_LEN);
                std::vector<uint8_t> got = My::hmac(key, message, hashFunc, blockSize, outputSize);

                if (verbose)
                {
                        std::cout << std::dec;
                        std::cout << "TEST " << i + 1 << "/" << n << "\n";
                        std::cout << "Key:\n";
                        for (uint8_t byte : key)
                        {
                                std::cout << std::hex << (int)byte;
                        }
                        std::cout << "\n";
                        std::cout << "Message:\n";
                        for (uint8_t byte : message)
                        {
                                std::cout << std::hex << (int)byte;
                        }
                        std::cout << "\n";
                        bool pass = testHMAC(key, message, got, md, outputSize);
                        if (pass)
                        {
                                std::cout << "PASS\n";
                                passed++;
                        }
                        else
                        {
                                std::cout << "FAIL\n";
                        }
                        std::cout << "\n";
                }
                else
                {
                        std::cout << "TEST " << i + 1 << "/" << n << " ";
                        bool pass = testHMAC(key, message, got, md, outputSize);
                        if (pass)
                        {
                                std::cout << "PASS\n";
                                passed++;
                        }
                        else
                        {
                                std::cout << "FAIL\n";
                        }
                }
        }
        std::cout << std::dec;
        std::cout << "\nPassed " << passed << "/" << n << " tests\n";
}

