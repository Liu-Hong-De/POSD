.PHONY: dirs clean stat

CC=g++
CFLAG=-std=c++11 -Wfatal-errors
all: clean dirs bin/ut_all

bin/ut_all: test/ut_main.cpp obj/find_visitor.o obj/update_path_visitor.o test/ut_fs.h src/file.h src/node.h src/folder.h src/utilities.h src/iterator.h src/null_iterator.h src/link.h src/visitor.h
	$(CC) $(CFLAG) -o $@ $< obj/find_visitor.o obj/update_path_visitor.o -lgtest -lpthread

obj/find_visitor.o: src/find_visitor.cpp src/find_visitor.h
		$(CC) $(CFLAG) -c $< -o $@

obj/update_path_visitor.o: src/update_path_visitor.cpp src/update_path_visitor.h
	$(CC) $(CFLAG) -c $< -o $@

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*
	rm -f obj/*

stat:
	wc -l src/* test/*.h test/*.cpp
