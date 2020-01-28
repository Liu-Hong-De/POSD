.PHONY: dirs clean stat

CC=g++
CFLAG=-std=c++11 -Wfatal-errors
all: clean dirs bin/ut_all

bin/ut_all: test/ut_midterm2.cpp obj/flattened_set_visitor.o obj/evaluate_visitor.o src/element.h src/integer.h src/iterator.h src/null_iterator.h src/set.h src/visitor.h
	$(CC) $(CFLAG) -o $@ $< obj/flattened_set_visitor.o obj/evaluate_visitor.o -lgtest -lpthread

obj/flattened_set_visitor.o: src/flattened_set_visitor.cpp src/flattened_set_visitor.h
	$(CC) $(CFLAG) -c $< -o $@

obj/evaluate_visitor.o: src/evaluate_visitor.cpp src/evaluate_visitor.h
	$(CC) $(CFLAG) -c $< -o $@

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*
	rm -f obj/*

stat:
	wc -l src/* test/*.h test/*.cpp
