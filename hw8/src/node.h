#ifndef NODE_H
#define NODE_H

#include <string>
#include <sys/stat.h>
#include <vector>
#include <regex>
#include <iostream>

#include "iterator.h"
#include "visitor.h"
#include "null_iterator.h"
#include "tree_frame.h"

using namespace std;

class Node {
public:
  Node(string path): _path(path) {
    if(lstat(path.c_str(), &_st) != 0) {
      throw string("Node is not exist!");
    }
  }

  virtual ~Node() {}

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

  int size() {
    return _st.st_size;
  }

  virtual void addChild(Node* child) {
    throw(std::string("Invalid add!"));
  }

  virtual Iterator* createIterator()=0;

  virtual void accept(Visitor *ibv)=0;

  virtual string fileOrNot()=0;

  string getPath()
  {
    // Getter!
    // return node path
    return this->_path;
  }

  void renameNode(string new_name)
  {
  /* You should update
    1. The physical node name.
    2. The node name in your own file system
  */
    string newPath;
    if(this->getParentPath() == this->getPath()) {
      newPath = new_name;
    }
    else {
      newPath = this->getParentPath() + "/" + new_name;
    }
    rename(this->getPath().c_str(), newPath.c_str());
    _path = newPath;
  }

  void updateParentPath(string parentPath){
    string newPath = parentPath + '/' + this->name();
    rename(this->getPath().c_str(), newPath.c_str());
    _path = newPath;
  }

  string getParentPath() {
    string path = this->getPath();
    for(int i = path.length() - 1; i >= 0; i--) {
      if (path[i] == '/') {
        path = path.substr(0, i);
        break;
      }
    }
    return path;
  }

  wxTreeItemId getWxTreeItemId() {
    return _wxTreeItemId;
  }

  void setWxTreeItemId(wxTreeItemId id) {
    this->_wxTreeItemId = id;
  }

  void updateSize(){
    lstat(_path.c_str(), &_st);
  }

private:
  string _path;
  struct stat _st;
  wxTreeItemId  _wxTreeItemId;
};


#endif
