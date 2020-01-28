#ifndef NODE_H
#define NODE_H

#include <string>
#include <sys/stat.h>
#include <sstream>
#include "infobyte_visitor.h"

class Node {
public:
  class Iterator{
  public:
    virtual bool isDone()=0;
    virtual void first()=0;
    virtual void next()=0;
    virtual Node* currentItem()=0;
  };
public:
  class NullIterator:public Iterator{
  public:
    bool isDone(){
      return true;
    }
    void first(){}
    void next(){}
    Node* currentItem(){
      return nullptr;
    }
  };

public:
  Node(std::string path): _path(path) {
    stat(_path.c_str(), &_st);
    extractNamesOfNodesOnPath(path);
  }

  virtual ~Node() {}

  int size() {
    return _st.st_size;
  }

  std::string name() const
  {
    return _namesOfNodesOnPath[_namesOfNodesOnPath.size()-1];
  }

  virtual void addChild(Node* child) {
    throw(std::string("Invalid add!"));
  }

  virtual Iterator* createIterator(){
    return new NullIterator();
  }

  virtual void accept(InfoByteVisitor &ibv)=0;

private:
  std::string _path;
  struct stat _st;
  std::vector<std::string> _namesOfNodesOnPath;

  void extractNamesOfNodesOnPath(std::string path)
  {
    char buf[256];
    std::istringstream ss(path);
    while (!ss.eof())
    {
      ss.get(buf, 256, '/');
      if (std::string(buf) != "")
        _namesOfNodesOnPath.push_back(buf);
      char skipChar;
      ss.get(skipChar);
    }
  }


};


#endif
