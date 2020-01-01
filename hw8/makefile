.PHONY:mkdir clean run stat
BIN=bin
OBJ=obj
SRC=src
TEST=test
CC=g++
CFLAG=-std=c++11 -Wfatal-errors

all:clean mkdir $(BIN)/tree_test

bin/hw8: $(SRC)/main.cpp
	g++ $(SRC)/main.cpp `wx-config --cxxflags --libs` -o $(BIN)/hw8 -lgtest -lpthread

$(OBJ)/text_frame.o: text_frame.cpp text_frame.h
	g++ -c $< `wx-config --cxxflags` -o $@ -lgtest -lpthread

$(BIN)/tree_test: $(SRC)/tree_test.cpp $(SRC)/tree_test.h $(SRC)/tree_frame.h
	g++ $< `wx-config --libs` `wx-config --cxxflags` -o $@ -lgtest -lpthread

run:
	$(BIN)/tree_test test

clean:
	rm -f $(BIN)/*

mkdir:
	mkdir -p $(BIN)
	mkdir -p $(OBJ)
