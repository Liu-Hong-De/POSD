.PHONY: dirs clean

all: dirs clean bin/ut_all

bin/ut_all: test/ut_main.cpp test/ut_file.h src/file.h
	g++ -std=c++11 -o $@ $< -lgtest -lpthread

dirs:
	mkdir -p bin

clean:
	rm -f bin/*
