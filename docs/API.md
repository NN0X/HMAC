# API Documentation

### [Go back to ABOUT](ABOUT.md)

### Table of contents

- [API](#api)
    - [HMAC.h](#hmach)
        - [hmac](#hmac)
        - [BlockSize](#blocksize)
        - [OutputSize](#outputsize)
    - [tests.h](#testsh)
        - [testRandomPairs](#testrandompairs)
- [Examples](#examples)
    - [Example 1](#hmac-with-sha-256)
    - [Example 2](#hmac-with-custom-hash-function)

## API

### [HMAC.h](../src/HMAC.h)

#### hmac

```c++
std::vector<uint8_t> My::hmac(std::vector<uint8_t> key,
                          std::vector<uint8_t> message,
                          unsigned char *(*hashFunc)(const unsigned char *,
                                                     size_t,
                                                     unsigned char *nullPass),
                          size_t blockSize,
                          size_t outputSize);
```

- **Description**: Calculates HMAC for given key and message.
- **Parameters**:
  - `key` - key used to calculate HMAC.
  - `message` - message to calculate HMAC for.
  - `hashFunc` - hash function used to calculate HMAC. Designed to work with functions supplied by OpenSSL.
    - `unsigned char *nullPass` - used to comply with OpenSSL function signature. Nothing is done with it.
  - `blockSize` - block size of hash function in bytes.
  - `outputSize` - output size of hash function in bytes.
- **Returns**: HMAC for given key and message as a vector of raw bytes.

#### BlockSize

```c++
enum My::BlockSize
        {
                SHA1_BLOCK = 64,
                SHA256_BLOCK = 64,
                SHA512_BLOCK = 128
        };
```

- **Description**: Block sizes for different hash functions.

#### OutputSize

```c++
enum My::OutputSize
        {
                SHA1_OUTPUT = 20,
                SHA256_OUTPUT = 32,
                SHA512_OUTPUT = 64
        };
```

- **Description**: Output sizes for different hash functions.

### [tests.h](../src/tests.h)

#### testRandomPairs

```c++
void testRandomPairs(int n,
                     unsigned char *(*hashFunc)(const unsigned char *,
                                                size_t,
                                                unsigned char *nullPass),
                     const EVP_MD *md,
                     size_t blockSize,
                     size_t outputSize);
```

- **Description**: Tests HMAC function with random key and message pairs.

### Examples

#### HMAC with SHA-256
```c++
#include <iostream>
#include <vector>
#include <iomanip>
#include <openssl/sha.h>

#include "HMAC.h"

int main()
{
    std::vector<uint8_t> key = { 'k', 'e', 'y' };
    std::vector<uint8_t> message = { 'm', 'e', 's', 's', 'a', 'g', 'e' };

    for (uint8_t byte : My::hmac(key, message, SHA256, My::SHA256_BLOCK, My::SHA256_OUT))
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (unsigned int)byte;
    }
    std::cout << std::endl;
    return 0;
}
```

- **Overview**: Calculates HMAC for key `key` and message `message` using OpenSSLs SHA-256 hash function and prints it in hexadecimal.

#### HMAC with custom hash function
```c++
#include <iostream>
#include <vector>
#include <iomanip>

#include "HMAC.h"

const int HASH_BLOCK_SIZE = 64;
const int HASH_OUTPUT_SIZE = 32;

unsigned char *customHash(const unsigned char *message, size_t messageSize, unsigned char *nullPass)
{
    unsigned char *hash = new unsigned char[HASH_OUTPUT_SIZE];

    // <- Hashing algorithm here ->

    return hash;
}

int main()
{
    std::vector<uint8_t> key = { 'k', 'e', 'y' };
    std::vector<uint8_t> message = { 'm', 'e', 's', 's', 'a', 'g', 'e' };

    for (uint8_t byte : My::hmac(key, message, customHash, HASH_BLOCK_SIZE, HASH_OUTPUT_SIZE))
    {
         std::cout << std::hex << std::setw(2) << std::setfill('0') << (unsigned int)byte;
    }
    std::cout << std::endl;
    return 0;
}
```

- **Overview**: Calculates HMAC for key `key` and message `message` using custom hash function `customHash` and prints it in hexadecimal.
