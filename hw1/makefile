.PHONY: clean

all: clean dirs bin/ut_all

bin/ut_all: test/ut_shape.cpp src/circle.h src/circular_sector.h src/rectangle.h src/ellipse.h src/triangle.h
	g++ -std=c++11 test/ut_shape.cpp -o bin/ut_all -lgtest -lpthread

clean:
	rm -f bin/*

dirs:
	mkdir -p bin
