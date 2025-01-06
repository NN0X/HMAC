# HMAC By NoX

Moja prosta implementacja algorytmu HMAC (Hash-based Message Authentication Code) w C++.

## Cel

Stworzyłem tę implementację jako projekt na uczelni. Jest to prosta implementacja algorytmu HMAC (Hash-based Message Authentication Code). Kod napisany jest w C++ i korzysta z biblioteki OpenSSL do hashowania.

## Instalacja

### Gotowe binaria

Gotowe pliki binarne są dostępne w zakładce [releases](https://github.com/NN0X/HMAC/releases).

### Budowanie ze źródła (tylko Linux)

Aby zbudować projekt ze źródła, polecam użycie dostarczonego Makefile. Domyślnym kompilatorem jest clang++, ale można to zmienić w Makefile. Projekt można zbudować jako bibliotekę statyczną lub jako samodzielny program wykonywalny z interfejsem CLI.

#### Budowanie jako biblioteka statyczna:

```bash
make static # biblioteka będzie w katalogu build
```

#### Budowanie jako samodzielny program wykonywalny:

```bash
make release # plik wykonywalny będzie w katalogu build
```

#### Budowanie wszystkiego:

```bash
make # biblioteka będzie w build/lib, a plik wykonywalny w build/release
```

### Budowanie ze źródła (Windows)

Nie testowałem budowania na Windowsie, ale powinno być to możliwe. Można użyć dostarczonego Makefile i uruchomić go za pomocą MinGW lub Cygwin. Alternatywą jest Visual Studio lub inne IDE wspierające C++, ale wymaga to ręcznego skonfigurowania projektu.

## Użycie

Do podstawowej funkcjonalności teoretycznie nie potrzeba dodatkowych bibliotek. Trzeba jednak dostarczyć funkcję hashującą kompatybilną z OpenSSL, dlatego sugeruję użycie właśnie OpenSSL. Powinno być ono preinstalowane w większości dystrybucji Linuxa. W przypadku Windowsa jest na przykład dołączone z dystrybucją Gita.

#### Interfejs CLI

Interfejs CLI to prosty sposób na użycie implementacji HMAC. Można go użyć do generowania HMAC dla podanej wiadomości i klucza. Domyślnie interfejs CLI korzysta z SHA512 jako funkcji hashującej, ale można to zmienić, podając żądaną funkcję jako argument (wersja CLI obsługuje SHA1, SHA256 i SHA512).

```bash
# Aby wygenerować HMAC z SHA512 dla podanego klucza i wiadomości
./main <klucz> <wiadomość>

# Aby wygenerować HMAC z określoną funkcją haszującą dla klucza i wiadomości
./main <klucz> <wiadomość> <funkcja_haszująca>

# przykład
./main klucz wiadomosc SHA256

# Aby włączyć tryb testowy (nie wiem, dlaczego miałbyś tego używać, ale jest dostępny)
./main test <liczba_losowych_par_klucz-wiadomosc>

# przykład
./main test 10
```

[!IMPORTANT] w przypadku używania `test` jako klucza komenda jest inna:

```bash
# ominięcie trybu testowego
./main test <wiadomość> -o
./main test <wiadomość> <funkcja_haszująca> -o

# przykład
./main test wiadomosc SHA1 -o
```

#### Biblioteka

Aby użyć biblioteki, trzeba dołączyć plik nagłówkowy i podlinkować bibliotekę. Biblioteka jest budowana jako statyczna, więc trzeba ją podlinkować statycznie. Domyślnie znajduje się ona w katalogu build.

```cpp
#include "HMAC.h"
```

```bash
# przykład podlinkowania biblioteki (bieżący katalog jest taki sam, jak katalog z biblioteką)
g++ main.cpp -o main -L. -lhmac
```

## Dokumentacja

Dokumentacja dostępna jest w katalogu [docs](docs). Napisałem ją samodzielnie i jest dostępna w dwóch językach: angielskim i polskim. Strona startowa to [[EN](docs/ABOUT.md#en)/[PL](docs/ABOUT.md#pl)]

## Licencja

Ta implementacja HMAC jest objęta licencją [Apache 2.0](LICENSE.md) oraz klauzulą [Common Clause](NOTICE.md).

### Użycie komercyjne

Jeśli chcesz używać tej implementacji komercyjnie, wiedz, że jak wskazano w [NOTICE](NOTICE.md), **nie masz na to pozwolenia**. Jeśli naprawdę chcesz użyć jej komercyjnie, proszę o kontakt.
