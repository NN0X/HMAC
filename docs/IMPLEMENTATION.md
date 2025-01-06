# My implementation of HMAC

### [Go back to ABOUT](ABOUT.md)

### Table of contents

- [Source excerpts](#source-excerpts)
  - [HMAC.cpp](#hmaccpp)
    - [Key padding](#key-padding)
    - [Inner and outer padding](#inner-and-outer-padding)
    - [Hashing](#hashing)
- [Library](#library)
- [Tests](#tests)

## Source excerpts

### [HMAC.cpp](../src/HMAC.cpp)

#### Key padding

```c++
***
if (key.size() > blockSize)
{
    unsigned char *keyPtr = hashFunc(key.data(), key.size(), NULL);
    key = std::vector<uint8_t>(keyPtr, keyPtr + outputSize);
}

if (key.size() < blockSize)
{
    key.resize(blockSize, ZERO);
}
***
```

- **Description**: Computes the block-sized key for HMAC.
- **Explanation**: If the key is longer than the block size, it is hashed. If the key is shorter than the block size, it is padded with zeros.

#### Inner and outer padding

```c++
***
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
***
```

- **Description**: Computes the inner and outer padding for HMAC.
- **Explanation**: The inner and outer padding are computed by XORing the key with the respective padding constant. The message is then appended to the inner padding.

#### Hashing

```c++
***
unsigned char *ipadHash = hashFunc(ipad.data(), ipad.size(), NULL);

opad.reserve(opad.size() + outputSize);
for (size_t i = 0; i < outputSize; i++)
{
    opad.push_back(ipadHash[i]);
}
unsigned char *opadHash = hashFunc(opad.data(), opad.size(), NULL);
***
```

- **Description**: Comutes inner and outer hashes for HMAC. Outer hash is the final HMAC.
- **Explanation**: The inner hash is computed by hashing the inner padding and the message. The outer hash is computed by hashing the outer padding and the inner hash.

## Library

This implementation was designed to be used as a library. The HMAC function is defined in [HMAC.h](../src/HMAC.h) and implemented in [HMAC.cpp](../src/HMAC.cpp). The library provides a simple interface for calculating HMAC with different hash functions provided by OpenSSL or by the user. It also includes enums for block sizes and output sizes of different hash functions. The library can be used with any hash function that conforms to the OpenSSL signature.

## Tests

To test the implementation, I used OpenSSL HMAC function with conjunction with key-message pair generation function. Then I compared the results of my implementation with the results of OpenSSL HMAC function. The test implementation can be found in [tests.cpp](../src/tests.cpp).
