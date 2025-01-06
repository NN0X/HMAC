# Moja implementacja HMAC

### [Powrót do ABOUT](../ABOUT.md)

### Spis treści

- [Fragmenty kodu źrodłowego](#fragmenty-kodu-źrodłowego)
  - [HMAC.cpp](#hmaccpp)
    - [Uzupełnianie klucza](#uzupełnianie-klucza)
    - [Wewnętrzne i zewnętrzne wypełnienie](#wewnętrzne-i-zewnętrzne-wypełnienie)
    - [Hashowanie](#hashowanie)
- [Biblioteka](#biblioteka)
- [Testy](#testy)

## Fragmenty kodu źrodłowego

### [HMAC.cpp](../src/HMAC.cpp)

#### Uzupełnianie klucza

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

- **Opis**: Oblicza klucz o rozmiarze bloku dla HMAC.
- **Wyjaśnienie**: Jeśli klucz jest dłuższy niż rozmiar bloku, jest hashowany. Jeśli klucz jest krótszy niż rozmiar bloku, jest uzupełniany zerami.

#### Wewnętrzne i zewnętrzne wypełnienie

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

- **Opis**: Oblicza wewnętrzne i zewnętrzne wypełnienie dla HMAC.
- **Wyjaśnienie**: Wewnętrzne i zewnętrzne wypełnienie są obliczane poprzez operację XOR klucza z odpowiednimi stałymi wypełnienia. Następnie do wewnętrznego wypełnienia jest dołączana wiadomość.

#### Hashowanie

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

- **Opis**: Oblicza wewnętrzny i zewnętrzny hash dla HMAC. Zewnętrzny hash jest końcowym kodem HMAC.
- **Wyjaśnienie**: Wewnętrzny hash jest obliczany poprzez hashowanie wewnętrznego wypełnienia i wiadomości. Zewnętrzny hash jest obliczany poprzez hashowanie zewnętrznego wypełnienia i wewnętrznego hasha.

## Biblioteka

Ta implementacja została zaprojektowana do używania jako biblioteka. Funkcja HMAC jest zdefiniowana w [HMAC.h](../src/HMAC.h) i zaimplementowana w [HMAC.cpp](../src/HMAC.cpp). Biblioteka zapewnia prosty interfejs do obliczania HMAC z różnych funkcji hashujących dostarczanych przez OpenSSL lub użytkownika. Zawiera również enumy dla rozmiarów bloków i wyników dla różnych funkcji hashujących. Bibliotekę można używać z dowolną funkcją hashującą spełniającą sygnaturę OpenSSL.

## Testy

Aby przetestować implementację, użyłem funkcji HMAC z OpenSSL w połączeniu z funkcją generowania pary klucz-wiadomość. Następnie porównałem wyniki mojej implementacji z wynikami funkcji HMAC z OpenSSL. Implementacja testów znajduje się w pliku [tests.cpp](../src/tests.cpp).


