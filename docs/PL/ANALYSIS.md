# HMAC teoria

### [Powrót do ABOUT](../ABOUT.md)

### Spis treści

- [Wprowadzenie](#wprowadzenie)
- [Terminologia](#terminologia)
- [Notacja](#notacja)
- [Algorytm](#algorytm)
- [Słabości](#słabości)
- [Źródła](#źródła)

## Wprowadzenie

Ponieważ każda funkcja hashująca może być użyta w HMAC, ważne jest, aby zrozumieć podstawy funkcji hashujących. Funkcje hashujące są używane do mapowania danych o dowolnym rozmiarze na wartości o stałej wielkości. Z tego powodu są często wykorzystywane w kryptografii do przechowywania haseł, generowania sum kontrolnych i innych. Funkcje hashujące są zaprojektowane tak, aby były nieodwracalne. Oznacza to, że jest to obliczeniowo nieopłacalne, aby odwrócić proces i uzyskać oryginalne dane z hasha. Ta właściwość jest kluczowa dla bezpieczeństwa HMAC. Warto zauważyć, że HMAC nie szyfruje wiadomości, a jedynie ją podpisuje. Oznacza to, że wiadomość niekoniecznie jest zaszyfrowana, ale weryfikowane jest, czy nie została zmieniona.

## Terminologia

- **MAC (Message Authentication Code)** - kryptograficzny kod używany do weryfikacji integralności i autentyczności wiadomości.
- **HMAC (Hash-based Message Authentication Code)** - specyficzny rodzaj MAC, który wykorzystuje kryptograficzną funkcję hashującą.
- **Funkcja hashująca** - funkcja, która mapuje dane o dowolnym rozmiarze na wartości o stałej wielkości.
- **Klucz** - tajna wartość używana do obliczenia HMAC.
- **Wiadomość** - dane, które są podpisywane przez HMAC.
- **Skrót** - wynik funkcji hashującej.
- **Rozmiar bloku** - rozmiar bloków, które funkcja hashująca przetwarza.
- **Rozmiar wyjścia** - rozmiar wyjścia funkcji hashującej.

## Notacja

- `||` - operator konkatenacji (np. `A || B` to konkatenacja `A` i `B`, więc `A || B = AB`).
- `⊕` - operator XOR (np. `A ⊕ B` to alternatywa wyłączająca dla `A` i `B`, więc 0b1111 ⊕ 0b1010 = 0b0101).

## Algorytm

### Definicja

HMAC jest zdefiniowane następująco:

```math
hmac(K, M) = H((K' ⊕ opad) || H((K' ⊕ ipad) || M))
```

gdzie:
- `K` to klucz.
- `M` to wiadomość.
- `H` to funkcja hashująca.
- `opad` to zewnętrzne opakowanie (0x5c powtarzane `blockSize` razy).
- `ipad` to wewnętrzna opakowanie (0x36 powtarzane `blockSize` razy).
- `K'` to klucz po wypełnieniu zerami do rozmiaru `blockSize` bajtów (jeśli klucz jest dłuższy niż `blockSize`, jest haszowany).

### Magiczne stałe

Magiczne stałe `0x36` i `0x5c` są używane jako padding. Zostały one wybrane przez twórcę HMAC arbitralnie z zastrzeżeniem, że są różne od siebie. Wybór tych stałych nie jest krytyczny dla bezpieczeństwa HMAC, jednak zostały one ustandaryzowane w specyfikacji HMAC w celu zapewnienia interoperacyjności. Mają one dużą odległość Hammingową, co jest pożądaną cechą dla stałych kryptograficznych.

## Słabości

HMAC jest uważany za bezpieczny, jednak zostały zidentyfikowane niektóre potencjalne słabości. Na przykład teoretycznie możliwe jest znalezienie długiego ciągu ASCII oraz losowej wartości, których hash również będzie ciągiem ASCII, a obie wartości wygenerują ten sam HMAC. Jak dotąd nie znaleziono praktycznych ataków, ale zaleca się używanie HMAC z bezpiecznymi funkcjami hashującymi (np. nie MD5).

## Źródła

- [RFC 2104](https://tools.ietf.org/html/rfc2104) - HMAC: Keyed-Hashing for Message Authentication
- [Wikipedia](https://en.wikipedia.org/wiki/HMAC) - HMAC
