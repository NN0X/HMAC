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

bool testHMAC(const std::string &key, const std::string &message, const std::string &got)
{
        // execute command line command
        std::string cmd = "echo -n \"" + message + "\" | openssl dgst -sha512 -hmac \"" + key + "\"";
        FILE *pipe = popen(cmd.c_str(), "r");
        if (!pipe)
        {
                std::cerr << "popen() failed" << std::endl;
                return false;
        }

        // read output
        char buffer[128];
        std::string expected;
        while (!feof(pipe))
        {
                if (fgets(buffer, 128, pipe) != NULL)
                {
                        expected += buffer;
                }
        }

        // get rid of everything but the hash
        expected = expected.substr(expected.find("= ") + 2);
        expected = expected.substr(0, expected.size() - 1);

        // close pipe
        pclose(pipe);

        return got == expected;
}

bool testSHA512(const std::string &message, const std::string &got)
{
        std::string cmd = "echo -n \"" + message + "\" | openssl dgst -sha512";
        FILE *pipe = popen(cmd.c_str(), "r");
        if (!pipe)
        {
                std::cerr << "popen() failed" << std::endl;
                return false;
        }

        // read output
        char buffer[128];
        std::string expected;
        while (!feof(pipe))
        {
                if (fgets(buffer, 128, pipe) != NULL)
                {
                        expected += buffer;
                }
        }

        expected = expected.substr(expected.find("= ") + 2);
        expected = expected.substr(0, expected.size() - 1);

        pclose(pipe);

        return got == expected;
}

int main(int argc, char *argv[])
{
        // FIX: Wrong output when message contains both upper and lower case letters

        if (argc != 3)
        {
                std::cout << "Usage: " << argv[0] << " <key> <message>" << std::endl;
                return 1;
        }

        std::string key = argv[1];
        std::string message = argv[2];

        // testing
        //key = "key";
        //message = "The quick brown fox jumps over the lazy dog";

        // sha test

        SHA512 sha512;
        std::string hashedTest = sha512.hash(message);
        std::cout << "SHA512 test: " << (testSHA512(message, hashedTest) ? "PASS" : "FAIL") << std::endl;

        std::vector<uint8_t> keyBytes(key.begin(), key.end());
        std::vector<uint8_t> messageBytes(message.begin(), message.end());

        std::vector<uint8_t> hashed = HMAC::hmacSHA512(keyBytes, messageBytes, hashSHA512, 128);

        std::string hashedStr(hashed.begin(), hashed.end());
        std::string hashedHex = bytesToHex(hashed);
        std::cout << "HMAC test: " << (testHMAC(key, message, hashedHex) ? "PASS" : "FAIL") << std::endl;

        return 0;
}
