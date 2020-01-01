#ifndef LINK_H
#define LINK_H

#include <sys/stat.h>
#include "node.h"

using namespace std;

class Link: public Node {
public:
  Link(string path, Node * node = nullptr): Node(path) // You should check path if it is not a link that you should throw string "It is not Link!"
  {
    struct stat st;
    if (lstat(path.c_str(), &st) == 0 && !S_ISLNK(st.st_mode)) {
      throw string("It is not Link!");
    }
    this->addLink(node);
  }

  void accept(Visitor* ibv) { // aceep visitor
    ibv->visitLink(this);
  }

  void addLink(Node * node) // add symbolic link
  {
    _link_node = node;
  }

  Node * getSource() // return node that the link point to!
  {
    return _link_node;
  }

  Iterator* createIterator() // return null Iterator
  {
    return new NullIterator();
  }

  string fileOrNot() {
    return "link";
  }

private:
  Node* _link_node;
};
#endif
