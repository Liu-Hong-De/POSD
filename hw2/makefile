.PHONY: clean

all: clean dirs bin/ut_all

bin/ut_all: src/main.cpp src/circle.h src/circular_sector.h src/rectangle.h src/ellipse.h src/triangle.h src/sort.h
	g++ -std=c++11 src/main.cpp -o bin/ut_all -lgtest -lpthread -Wfatal-errors

clean:
	rm -f bin/*

dirs:
	mkdir -p bin
