# Dokumentacja API

### [Powrót do ABOUT](../ABOUT.md)

### Spis treści

- [API](#api)
    - [HMAC.h](#hmach)
        - [hmac](#hmac)
        - [BlockSize](#blocksize)
        - [OutputSize](#outputsize)
    - [tests.h](#testsh)
        - [testRandomPairs](#testrandompairs)
- [Przykłady](#przykłady)
    - [Przykład 1](#hmac-z-użyciem-sha-256)
    - [Przykład 2](#hmac-z-użyciem-własnej-funkcji-hashującej)

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

- **Opis**: Oblicza HMAC dla podanego klucza i wiadomości.
- **Parametry**:
  - `key` - klucz używany do obliczenia HMAC.
  - `message` - wiadomość, dla której obliczany jest HMAC.
  - `hashFunc` - funkcja hashująca używana do obliczenia HMAC. Zaprojektowana z myślą o funkcjach OpenSSL.
    - `unsigned char *nullPass` - używane w celu zgodności z sygnaturą funkcji OpenSSL. Nie jest wykorzystywane.
  - `blockSize` - rozmiar bloku funkcji hashującej w bajtach.
  - `outputSize` - rozmiar wyjścia funkcji hashującej w bajtach.
- **Zwraca**: HMAC dla podanego klucza i wiadomości w formie wektora surowych bajtów.

#### BlockSize

```cpp
enum My::BlockSize
        {
                SHA1_BLOCK = 64,
                SHA256_BLOCK = 64,
                SHA512_BLOCK = 128
        };
```

- **Opis**: Rozmiary bloków dla różnych funkcji hashujących.

#### OutputSize

```cpp
enum My::OutputSize
        {
                SHA1_OUTPUT = 20,
                SHA256_OUTPUT = 32,
                SHA512_OUTPUT = 64
        };
```

- **Opis**: Rozmiary wyjściowe dla różnych funkcji hashujących.

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

- **Opis**: Testuje funkcję HMAC z losowymi parami klucz-wiadomość.

## Przykłady

### HMAC z użyciem SHA-256

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

- **Opis**: Oblicza HMAC dla klucza `key` i wiadomości `message` przy użyciu funkcji hashującej SHA-256 z biblioteki OpenSSL i wypisuje wynik w formacie szesnastkowym.

### HMAC z użyciem własnej funkcji hashującej

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

    // <- Algorytm hashujący tutaj ->

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

- **Opis**: Oblicza HMAC dla klucza `key` i wiadomości `message` przy użyciu własnej funkcji hashującej `customHash` i wypisuje wynik w formacie szesnastkowym.
