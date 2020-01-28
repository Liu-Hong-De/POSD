.PHONY: clean run mkdir
BIN=bin
SRC=src
TEST=test

all: clean mkdir midterm
midterm:  $(TEST)/ut_main.cpp $(SRC)/solid.h $(SRC)/complex_solids.h $(SRC)/square_cylinder.h $(SRC)/cone.h $(SRC)/triangular_pyramid.h $(TEST)/ut_solid.h
		g++ -std=c++11 $(TEST)/ut_main.cpp -o $(BIN)/ut_all  -lgtest -lpthread

clean:
		rm -f $(BIN)/*
run:
		$(BIN)/ut_all
mkdir:
		mkdir -p $(BIN)
