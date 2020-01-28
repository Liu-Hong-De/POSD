#ifndef NODE_H
#define NODE_H

#include <string>
#include <regex>
#include <iostream>
#include <sys/stat.h>

using namespace std;

class Node {
public:
  Node(std::string path): _path(path) {
    if(stat(_path.c_str(), &_st) == 0){}
    else {
      throw(std::string("Node is not exist!"));
    }
  }

  int size() {
    return _st.st_size;
  }

  virtual void addChild(Node* child) {
    throw(std::string("Invalid add!"));
  }

  virtual Node* getChild(int num) {
    return NULL;
  }

  virtual int infoByte(){
    return size();
  }

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

  virtual string allNode() {
    return name();
  }

  virtual string allLeaf() {
    return name();
  }

  virtual string allNodePath(string begin) {
    return name();
  }

  virtual vector<string> split(const string& str, const string& delim) {
    std::vector<string> v;
    return v;
  }

  virtual string findNode(string name)
  {
      // implementation findNode
      // folder->findNode(name) that should find all nodes(include child nodes and all offspring) under it.
      // file->findNode(name) that should find itself.
      // if find two nodes or more than two nodes.
      // Result should be separated by '\n'.
      return name;
  }

  virtual string listNode()
  {
      // implementation list child Node and Sort by dictionary
      // Result should be separated by space
      // For example:
      // Folder contains childnode "a.out" and "TA_folder" and "hello.txt"
      // It should return "TA_folder a.out hello.txt"
      // If node is file, it can't listNode.
      // It should throw "Not a directory"
      // For Example: TA_file->listNode()
      throw(std::string("Not a directory"));
      return "";
    }

private:
  std::string _path;
  struct stat _st;
};

//pratice here
int infoByte(Node* node) {
  int total = 0;
  if (node->getChild(0) != nullptr) { //it's a folder
    for(int i = 0; i < 2; i++){
      total += node->getChild(i)->size();
    }
  }
  return total;
}
#endif
