CXX = clang++
CFLAGS = -O3 -Wall -Wextra -Wpedantic -lssl -lcrypto
SRC = src
OUT = main
HEADER = HMAC
LIBNAME = hmac

all:
	rm -f -r build
	mkdir build
	mkdir build/release
	$(CXX) $(CFLAGS) $(SRC)/*.cpp -o build/release/$(OUT) 2> build/release/make.log
	cp *.md build/release/
	
	mkdir build/lib
	$(CXX) $(CFLAGS) -c $(filter-out $(SRC)/main.cpp, $(wildcard $(SRC)/*.cpp)) 2> build/lib/make.log
	ar rcs build/lib/lib$(LIBNAME).a *.o
	rm *.o
	cp src/$(HEADER).h build/lib/$(HEADER).h
	cp *.md build/lib/
	cp -r docs build/

release:
	rm -f -r build
	mkdir build
	$(CXX) $(CFLAGS) $(SRC)/*.cpp -o build/$(OUT) 2> build/make.log
	cp *.md build/
	cp -r docs build/

static:
	rm -f -r build
	mkdir build
	$(CXX) $(CFLAGS) -c $(filter-out $(SRC)/main.cpp, $(wildcard $(SRC)/*.cpp)) 2> build/make.log
	ar rcs build/lib$(LIBNAME).a *.o
	rm *.o
	cp src/$(HEADER).h build/$(HEADER).h
	cp *.md build/
	cp -r docs build/
