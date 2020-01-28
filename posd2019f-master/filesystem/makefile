.PHONY: dirs clean stat

CC=g++
CFLAG=-std=c++11 -Wfatal-errors
all: dirs bin/ut_all bin/ui_folder_tree

bin/ut_all: test/ut_main.cpp obj/infobyte_visitor.o test/ut_file.h src/file.h src/node.h src/folder.h src/link.h src/filesystem_builder.h src/utilities.h
	$(CC) $(CFLAG) -o $@ $< obj/infobyte_visitor.o -lgtest -lpthread

obj/infobyte_visitor.o: src/infobyte_visitor.cpp src/infobyte_visitor.h
	$(CC) $(CFLAG) -c $< -o $@

bin/ui_folder_tree: test/ui_folder_tree.cpp test/ui_folder_tree.h test/tree_frame.h
		g++ $< `wx-config --libs` `wx-config --cxxflags` obj/infobyte_visitor.o -o $@

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*

stat:
	wc -l src/* test/*.h test/*.cpp
