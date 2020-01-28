#ifndef LINK_H
#define LINK_H
#include <sys/stat.h>
#include "node.h"

class Link : public Node{
public:
  Link(string path, Node * node = nullptr) : Node(path)
  {
    if(!S_ISLNK(Node::getStat().st_mode))
      throw std::string("It is not Link!");
    this->addLink(node);
  }

  void addLink(Node * node)
  {
    _source = node;
  }

  Node * getSource() {
    return _source;
  }

  Iterator* createIterator(){
    return new Node::NullIterator();
  }

private:
  Node * _source;
};

#endif
