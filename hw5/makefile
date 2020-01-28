.PHONY: dirs clean

all: dirs bin/ut_all

bin/ut_all: test/ut_main.cpp test/ut_fs.h src/file.h src/node.h src/folder.h src/utilities.h src/iterator.h src/null_iterator.h
	g++ -std=c++11 -Wfatal-errors -o $@ $< -lgtest -lpthread

dirs:
	mkdir -p bin

clean:
	rm -f bin/*
