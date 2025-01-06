# Przykłady wstępnie obliczonych HMAC

### [Powrót do ABOUT](../ABOUT.md)

### Spis treści

- [SHA1](#sha1)
    - [Przykład 1](#przykład-1)
    - [Przykład 2](#przykład-2)
- [SHA256](#sha256)
    - [Przykład 3](#przykład-3)
    - [Przykład 4](#przykład-4)
- [SHA512](#sha512)
    - [Przykład 5](#przykład-5)
    - [Przykład 6](#przykład-6)

## SHA1

### Przykład 1

- **Klucz**: `key`
- **Wiadomość**: `The quick brown fox jumps over the lazy dog` (Wiadomość zawierająca wszystkie 26 liter alfabetu angielskiego)
- **HMAC**: `de7c9b85b8b78aa6bc8a7a36f70a90701c9db4d9`

### Przykład 2

- **Klucz**: `klucz`
- **Wiadomość**: `Zażółć gęślą jaźń` (Wiadomość zawierająca wszystkie polskie znaki diakrytyczne)
- **HMAC**: `e31446607b617028ef2ab40e8244dbcd0f4fca80`

## SHA256

### Przykład 3

- **Klucz**: `key`
- **Wiadomość**: `The quick brown fox jumps over the lazy dog`
- **HMAC**: `f7bc83f430538424b13298e6aa6fb143ef4d59a14946175997479dbc2d1a3cd8`

### Przykład 4

- **Klucz**: `klucz`
- **Wiadomość**: `Zażółć gęślą jaźń`
- **HMAC**: `132a1bf1667c0818b045add5e9136258f7d3234362b383611e3243cb7327e1de`

## SHA512

### Przykład 5

- **Klucz**: `key`
- **Wiadomość**: `The quick brown fox jumps over the lazy dog`
- **HMAC**: `b42af09057bac1e2d41708e48a902e09b5ff7f12ab428a4fe86653c73dd248fb82f948a549f7b791a5b41915ee4d1ec3935357e4e2317250d0372afa2ebeeb3a`

### Przykład 6

- **Klucz**: `klucz`
- **Wiadomość**: `Zażółć gęślą jaźń`
- **HMAC**: `a3a9aba18d32444efbfbd47718d4783761a5865aacf4c8782320611033f86ec169be13343ff0f4c8f56d88b690567476e146a4d180a90da8a7ea29910da96508`

