#ifndef NODE_H
#define NODE_H

#include <string>
#include <sys/stat.h>
#include <regex>

#include "iterator.h"

using namespace std;

class Node {
public:
  Node(std::string path): _path(path) {
    stat(_path.c_str(), &_st);
  }

  int size() {
    return _st.st_size;
  }

  virtual void addChild(Node* child) {
    throw(string("Invalid add!"));
  }

  virtual Iterator* createIterator()=0;

  string name()
  {
    // For example path:"test/TA_folder/hello.txt"
    // "hello.txt" is name
    // Return "hello.txt"
    smatch name;
    regex nameType("[^/]*$");
    while(regex_search(_path, name, nameType)) {
      return name[0];
    }
  }

private:
  std::string _path;
  struct stat _st;
};

#endif
