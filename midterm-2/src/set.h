#ifndef SET_H
#define SET_H

#include <vector>
#include <string>

#include "element.h"

using namespace std;

class Set: public Element {
public:
  class SetIterator:public Iterator {
  public:
    SetIterator(Set * s): _s(s) {}

    void first() {
      _current = _s->_v.begin();
    }

    Element * currentItem() {
      if(isDone()) {
        throw(string("No current item!"));
      }
      return *_current;
    }

    void next() {
      if(isDone()) {
        throw(string("Moving past the end!"));
      }
      ++_current;
    }

    bool isDone() {
      return _current == _s->_v.end();
    }
  private:
    Set * _s;
    vector<Element *>::iterator _current;
  };
public:
  Set(){

  }

  void add(Element * element) {
    _v.push_back(element);
  }

  int size() {
    return _v.size();
  }

  string toString() {
    string a = "{";
    Iterator * it = this->createIterator();
    if(!it->isDone()) {
      for(it->first(); !it->isDone();) {
        a += it->currentItem()->toString();
        a += ",";
        try{it->next();}
        catch(string message) {break;}
      }
      a = a.substr(0, a.length()-1);
    }
    a += "}";
    return a;
  }

  Iterator * createIterator() {
    return new SetIterator(this);
  }

  void setOperator(char ope) {
    if(ope != '+' || ope != '-' || ope != '*' || ope != '/') {
      throw(string("Invalid operator!"));
    }
  }

  void accept(Visitor * visitor) {
     visitor->visitSet(this);
  }

private:
  vector<Element*> _v;
  char _ope;

};
#endif
