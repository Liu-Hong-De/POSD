#ifndef COMPLEX_SOLIDS_H
#define COMPLEX_SOLIDS_H

#include <vector>

#include "solid.h"

class ComplexSolids
{
public:
  class SolidIterator {
  public:
    SolidIterator(ComplexSolids * f): _f(f) {}

    void first() {
      _current = _f->_solids->begin();
      // _current = *(_f->_v.begin());
    }

    Solid * currentItem() {
      return *_current;
    }

    void next() {
      ++_current;
    }

    bool isDone() {
      return _current == _f->_solids->end();
    }
  private:
    ComplexSolids * _f;
    std::vector<Solid *>::iterator _current;
    // Node * _current;
  };
public:
    ComplexSolids(std::vector<Solid*> * solids): _solids(solids) {

    }

    SolidIterator * createIterator() {
      return new SolidIterator(this);
    }

    void add(Solid *s) {
      _solids->push_back(s);
    }

    double bottomArea()
    {
      double total = 0;
      SolidIterator * it = createIterator();
      for(it->first(); !it->isDone(); it->next()) {
        total += it->currentItem()->bottomArea();
      }
      return total;
    }
    double volume()
    {
      double total = 0;
      SolidIterator * it = createIterator();
      for(it->first(); !it->isDone(); it->next()) {
        total += it->currentItem()->volume();
      }
      return total;
    }

    int numberOfChild()
    {
      int count = 0;
      SolidIterator * it = createIterator();
      for(it->first(); !it->isDone(); it->next()) {
        count++;
      }
      return count;
    }

private:
  std::vector<Solid*>* _solids;
};
#endif
