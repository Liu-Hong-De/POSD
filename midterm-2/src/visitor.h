#ifndef VISITOR_H
#define VISITOR_H

class Integer;
class Set;

#include <string>

using namespace std;

class Visitor {
public:
  virtual void visitInteger(Integer * i) = 0;
  virtual void visitSet(Set * s) = 0;
};
#endif
