#include <fstream>
#include <iostream>
#include <string>
#include "terminal.h"

int main(int argc, char *argv[]){
      // argv you can see makefile "bin/geo input.txt output.txt area inc"
      // argv[1] = input.txt, argv[2] = output.txt, argv[3] = area, argv[4] = inc
      // implement reading input.txt
      // compose the string to Terminal(** Input string **)
      // **Input string**  Example: "Ellipse (6,5) Triangle (3,0,0,2,-3,0) CircularSector (8,40) area inc"
      // call showResult() to get result
      // write the result to output.txt
      // Don't hard code!!!
      const int MAX = 100;
      char buffer[MAX];   // store input string

      fstream infile;
      string line;      // store request

      infile.open("input.txt", ios::in);
      if (!infile)
        cout << "file can not open" << endl;
      else {
        do {
          infile.getline(buffer, sizeof(buffer));
          line += buffer;
        } while(!infile.eof());
        infile.close();
      }

      line.insert(line.length()-1, " ");
      line.insert(line.length()-1, argv[3]);
      line.insert(line.length()-1, " ");
      line.insert(line.length()-1, argv[4]);

      fstream outfile;
      outfile.open("output.txt", ios::out);
      if(!outfile)
        cout << "file can not open" << endl;
      else {
        Terminal * test = new Terminal(line);
        outfile << test->showResult();
        outfile.close();
      }

      return 0;
}
