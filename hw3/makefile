.PHONY: clean run mkdir
BIN=bin
SRC=src
TEST=test

all: clean mkdir hw3 geo execute
hw3:  $(TEST)/ut_main.cpp $(TEST)/ut_sort.h $(SRC)/shape.h $(SRC)/ellipse.h $(SRC)/triangle.h $(SRC)/triangle.h $(SRC)/circular_sector.h $(SRC)/sort.h $(SRC)/terminal.h
		g++ -std=c++11 -Wfatal-errors $(TEST)/ut_main.cpp -o $(BIN)/ut_all  -lgtest -lpthread

geo: $(SRC)/main.cpp $(TEST)/ut_sort.h $(SRC)/shape.h $(SRC)/ellipse.h $(SRC)/triangle.h $(SRC)/triangle.h $(SRC)/circular_sector.h $(SRC)/sort.h $(SRC)/terminal.h
		g++ -std=c++11 $(SRC)/main.cpp -o $(BIN)/geo  -lgtest -lpthread

execute:
		bin/geo input.txt output.txt area inc

clean:
		rm -f $(BIN)/* rm -f output.txt
run:
		$(BIN)/ut_all
mkdir:
		mkdir -p $(BIN)
