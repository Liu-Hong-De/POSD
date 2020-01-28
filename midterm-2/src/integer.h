#ifndef INTEGER_H
#define INTEGER_H

#include <string>
#include <iostream>

#include "element.h"

using namespace std;

class Integer: public Element {
public:
  Integer(int i): _i(i)
  {

  }

  void add(Element * element) {
    throw(string("It's an integer!"));
  }

  int size() {
    return 1;
  }

  string toString() {
    return to_string(_i);
  }

  Iterator * createIterator() {
    return new NullIterator();
  }

  void setOperator(char c) {
    throw(string("Cannot set operator on it!"));
  }

  void accept(Visitor * visitor) {
    visitor->visitInteger(this);
  }

private:
  int _i;
};
#endif
