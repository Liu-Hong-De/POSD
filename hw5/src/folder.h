#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <sys/stat.h>
#include <vector>
#include <map>

#include "node.h"

class Folder: public Node {
public:
  class FolderIterator:public Iterator {
  public:
    FolderIterator(Folder * f): _f(f) {


    }

    void first() {
      // if(!isDone()) {
        _current = _f->_v.begin();
      // }
      // _current = *(_f->_v.begin());
    }

    Node * currentItem() {
      if(isDone()){
        throw(std::string("No current item!"));
      }
      else{
        return _current->second;
      }
    }

    void next() {
      if(isDone()) {
        throw(std::string("Moving past the end!"));
      }
      else {
        ++_current;
      }
    }

    bool isDone() {
      return _current == _f->_v.end();
    }
  private:
    Folder * _f;
    std::map<std::string, Node *>::iterator _current;
    // Node * _current;
  };
public:
  Folder(std::string path): Node(path) {}

  void addChild(Node* child) {
    _v.insert(std::pair<std::string, Node *>(child->name(), child));
  }

  Iterator * createIterator() {
    return new FolderIterator(this);
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
  std::map<std::string, Node *> _v;
};
#endif
