#ifndef TESTS_H
#define TESTS_H

#include <openssl/evp.h>

void testRandomPairs(int n, unsigned char *(*hashFunc)(const unsigned char *, size_t, unsigned char *nullPass), const EVP_MD *md, size_t blockSize, size_t outputSize);

#endif
