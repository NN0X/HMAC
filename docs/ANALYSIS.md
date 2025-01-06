# HMAC Simple Theory

### [Go back to ABOUT](ABOUT.md)

### Table of contents

- [Introduction](#introduction)
- [Terminology](#terminology)
- [Notation](#notation)
- [Algorithm](#algorithm)
- [Weaknesses](#weaknesses)
- [References](#references)

## Introduction

As any hashing function can be used in HMAC, it is important to understand the basics of hashing functions. Hashing functions are used to map data of arbitrary size to fixed-size values. Because of this, they are often used in cryptography to store passwords, generate checksums, and more. Hashing functions are designed to be irreversible. This means that it is computationally infeasible to reverse the process and obtain the original data from the hash. This property is crucial for the security of HMAC. It is important to note that HMAC doesn't encrypt the message, but rather signs it. This means that the message is not necessarily hidden, but it is verified that it was not tampered with.

## Terminology

- **MAC (Message Authentication Code)** - a cryptographic code used to verify the integrity and authenticity of a message.
- **HMAC (Hash-based Message Authentication Code)** - a specific type of MAC that uses a cryptographic hash function.
- **Hash function** - a function that maps data of arbitrary size to fixed-size values.
- **Key** - a secret value used to calculate the HMAC.
- **Message** - data that is signed by the HMAC.
- **Digest** - the output of the hash function.
- **Block size** - the size of the blocks that the hash function processes.
- **Output size** - the size of the output of the hash function.

## Notation

- `||` - concatenation operator (e.g. `A || B` is the concatenation of `A` and `B` so that `A || B = AB`).
- `⊕` - XOR operator (e.g. `A ⊕ B` is the exclusive or of `A` and `B` so that 0b1111 ⊕ 0b1010 = 0b0101).

## Algorithm

### Definition

HMAC is defined as follows:

```math
hmac(K, M) = H((K' ⊕ opad) || H((K' ⊕ ipad) || M))
```

where:
- `K` is the key.
- `M` is the message.
- `H` is the hash function.
- `opad` is the outer padding (0x5c repeated `blockSize` times).
- `ipad` is the inner padding (0x36 repeated `blockSize` times).
- `K'` is the key after padding with zeros to `blockSize` bytes (if the key is longer than `blockSize`, it is hashed).

### Magic constants

The magic constants `0x36` and `0x5c` are used as padding. They were selected by creator of HMAC arbitrarily with the caveat that they are different from each other. The choice of these constants is not critical for the security of HMAC, however they were standardized in the HMAC specification to ensure interoperability. They do have a large Hamming distance, which is a desirable property for cryptographic constants.

## Weaknesses

HMAC is considered to be secure, however some potential weaknesses have been identified. It is for example theoretically possible to find a long ASCII string and a random value whose hash will be also an ASCII string, and both values will produce the same HMAC output. As of now, no practical attacks have been found, but it is recommended to use HMAC with secure hash functions(e.g. not MD5).

## References

- [RFC 2104](https://tools.ietf.org/html/rfc2104) - HMAC: Keyed-Hashing for Message Authentication
- [Wikipedia](https://en.wikipedia.org/wiki/HMAC) - HMAC
