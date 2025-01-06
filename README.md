# HMAC by NoX

My simple implementation of HMAC (Hash-based Message Authentication Code) algorithm in C++.

## Purpose

I created this implementation as a university project. It is a simple implementation of HMAC (Hash-based Message Authentication Code) algorithm. It is written in C++ and uses OpenSSL library for hashing.

## Installation

### Pre-built binaries

You can download pre-built binaries from the [releases](https://github.com/NN0X/HMAC/releases) page.

### Building from source (Linux-only)

To build this project from source I recommend using the provided Makefile. The default compiler is clang++ but you can change it in the Makefile. You can build the project as a static library or as a standalone executable with my CLI interface.

#### Building as a static library run:
```bash
make static # the library will be in the build directory
```
#### Building as a standalone executable run:
```bash
make release # the executable will be in the build directory
```
#### Building all:
```bash
make # library will be in build/lib and executable in build/release
```

### Building from source (Windows)

I haven't tested building on Windows but it should be possible. You can use the provided Makefile and run it with MinGW or Cygwin. You can also use Visual Studio or any other IDE that supports C++ but you will have to create a project yourself.

## Usage

For the basic functionality you don't theoretically need any additional libraries. However, you have to provide hashing function compatible with OpenSSL so I suggest using OpenSSL. It should come pre-installed on most Linux distributions. If you are using Windows, it is for example included with Git.

#### CLI interface

The CLI interface is a simple way to use the HMAC implementation. You can use it to generate HMAC for a given message and key. By default, the CLI interface uses SHA512 as the hashing function but you can change it by specifying the desired function as an argument (CLI version supports SHA1, SHA256 and SHA512).
```bash
# To generate HMAC with SHA512 and specified key-message pair
./main <key> <message>

# To generate HMAC with specified hashing function and key-message pair
./main <key> <message> <hashing_function>

# example
./main key message SHA256

# To use testing mode (I don't know why you would want to use it but it's there)
./main test <number_of_random_key-message_pairs>

# example
./main test 10
```

[!IMPORTANT] when using `test` as the key the usage is different:
```bash
# override test mode
./main test <message> -o
./main test <message> <hashing_function> -o

# example
./main test message SHA1 -o
```
#### Library

To use the library you have to include the header file and link the library. The library is built as a static library so you have to link it statically. The library is in the build directory.

```cpp
#include "HMAC.h"
```

```bash
# example of linking the library (current directory is the same as libhmac.a)
g++ main.cpp -o main -L. -lhmac
```

## Documentation

The documentation is available in the [docs](docs) directory. It is written by my and available in two languages: English and Polish. The starting page is [[EN](docs/ABOUT.md#en)/[PL](docs/ABOUT.md#pl)]

## License

This implementation of HMAC is under [Apache 2.0](LICENSE.md) license and [Common Clause](NOTICE.md).

### Commercial use

If you want to use this implementation commercially, know that, as stated in [NOTICE](NOTICE.md), **you are not allowed**. If you really want to use it commercially, please contact me.
