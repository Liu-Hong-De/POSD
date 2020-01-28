.PHONY: clean

all: ut_hello hello
		
hello: src/hello.cpp
	g++ src/hello.cpp -o bin/hello

ut_hello: test/ut_hello.cpp src/hello_posd.h
	g++ test/ut_hello.cpp -o bin/ut_hello -lgtest -lpthread

clean:
	rm -f bin/*
