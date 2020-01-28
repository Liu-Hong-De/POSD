.PHONY: clean

all: bin/ut_main

bin/ut_main: test/ut_main.cpp src/circle.h src/rectangle.h test/ut_shape.h test/ut_sort.h
	g++ -std=c++11 test/ut_main.cpp -o bin/ut_main -lgtest -lpthread

clean:
	rm bin/*
