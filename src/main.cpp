#include <iostream>

#include "SHA512.h"
#include "HMAC.h"

std::string bytesToHex(const std::vector<uint8_t> &bytes)
{
        std::string hex;
        for (size_t i = 0; i < bytes.size(); i++)
        {
                hex += "0123456789abcdef"[bytes[i] >> 4];
                hex += "0123456789abcdef"[bytes[i] & 0xf];
        }
        return hex;
}

std::vector<uint8_t> hexToBytes(const std::string &hex)
{
        // 0123456789abcdef
        std::vector<uint8_t> bytes;
        for (size_t i = 0; i < hex.size(); i += 2)
        {
                uint8_t byte = std::stoi(hex.substr(i, 2), nullptr, 16);
                bytes.push_back(byte);
        }
        return bytes;
}

std::vector<uint8_t> hashSHA512(const std::vector<uint8_t> &message)
{
        std::string messageStr(message.begin(), message.end());
        SHA512 sha512;
        std::string hashed = sha512.hash(messageStr);

        return hexToBytes(hashed);
}

int main()
{
        // FIX: Wrong output when message contains capital letters

        std::string key = "key";
        std::string message = "The quick brown fox jumps over the lazy dog";

        std::vector<uint8_t> keyBytes(key.begin(), key.end());
        std::vector<uint8_t> messageBytes(message.begin(), message.end());

        std::vector<uint8_t> hashed = HMAC::hmacSHA512(keyBytes, messageBytes, hashSHA512, 128);

        std::string hashedStr(hashed.begin(), hashed.end());
        std::string hashedHex = bytesToHex(hashed);

        std::string expOut = "b42af09057bac1e2d41708e48a902e09b5ff7f12ab428a4fe86653c73dd248fb82f948a549f7b791a5b41915ee4d1ec3935357e4e2317250d0372afa2ebeeb3a";

        if (hashedHex == expOut)
        {
                std::cout << "HASH: " << hashedHex << std::endl;
                std::cout << "Test passed" << std::endl;
        }
        else
        {
                std::cout << "HASH: " << hashedHex << std::endl;
                std::cout << "Test failed" << std::endl;
        }

        return 0;
}
