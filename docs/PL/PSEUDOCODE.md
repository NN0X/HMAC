# Pseudokod dla algorytmu HMAC

### [Powrót do ABOUT](../ABOUT.md)

## Pseudokod

```plaintext
funkcja hmac jest
    wejście:
        klucz:      Bajty    // Tablica bajtów
        wiadomość:  Bajty    // Tablica bajtów do haszowania
        funkcjaHash: Funkcja // Funkcja hashująca do użycia (np. SHA-1)
        rozmiarBloku:  Liczba  // Rozmiar bloku funkcji hashującej (np. 64 bajty dla SHA-1)
        rozmiarWyjścia: Liczba  // Rozmiar wyjścia funkcji hashującej (np. 20 bajtów dla SHA-1)

    // Obliczanie klucza o rozmiarze bloku
    kluczRozmiarBloku = obliczKluczRozmiarBloku(klucz, funkcjaHash, rozmiarBloku)

    opad ← kluczRozmiarBloku xor [0x5c rozmiarBloku]
    ipad ← kluczRozmiarBloku xor [0x36 rozmiarBloku]

    zwróć  funkcjaHash(opad ∥ funkcjaHash(ipad ∥ wiadomość))

funkcja obliczKluczRozmiarBloku jest
    wejście:
        klucz:      Bajty    // Tablica bajtów
        funkcjaHash: Funkcja // Funkcja hashująca do użycia (np. SHA-1)
        rozmiarBloku: Liczba  // Rozmiar bloku funkcji hashującej (np. 64 bajty dla SHA-1)

    jeśli (długość(klucz) > rozmiarBloku) wtedy
        klucz = funkcjaHash(klucz)

    jeśli (długość(klucz) < rozmiarBloku) wtedy
        zwróć  Pad(klucz, rozmiarBloku)

    zwróć  klucz
```
