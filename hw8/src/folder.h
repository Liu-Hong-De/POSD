#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <sys/stat.h>
#include <vector>
#include <map>

#include "node.h"

using namespace std;

class Folder: public Node {
public:
  class FolderIterator:public Iterator {
  public:
    FolderIterator(Folder * f): _f(f) {}

    void first() {
      _current = _f->_v.begin();
    }

    Node * currentItem() {
      return _current->second;
    }

    void next() {
      ++_current;
    }

    bool isDone() {
      return _current == _f->_v.end();
    }
  private:
    Folder * _f;
    map<string, Node *>::iterator _current;
  };
public:
  Folder(std::string path): Node(path) {
    struct stat st;
    if (lstat(path.c_str(), &st) == 0 && !S_ISDIR(st.st_mode)) {
      throw string("It is not Folder!");
    }
  }

  void addChild(Node* child) {
    _v.insert(pair<string, Node*>(child->name(), child));
  }

  Iterator * createIterator() {
    return new FolderIterator(this);
  }

  void accept(Visitor* ibv) {
    ibv->visitFolder(this);
  }

  string fileOrNot() {
    return "folder";
  }

  bool isEmpty() {
    if(_v.empty()) {
      return true;
    }
    else{
      return false;
    }
  }

private:
  map<string, Node*> _v;
};
#endif
