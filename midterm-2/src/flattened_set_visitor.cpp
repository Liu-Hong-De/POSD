#include "flattened_set_visitor.h"
#include "integer.h"
#include "set.h"
#include "element.h"
#include "iterator.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

FlattenedSetVisitor::FlattenedSetVisitor()
{

}

void FlattenedSetVisitor::visitInteger(Integer * i){
  _fv.push_back(i);
}

void FlattenedSetVisitor::visitSet(Set * s){
  Iterator *it = s->createIterator();
  for (it->first(); !it->isDone(); it->next()) {
    it->currentItem()->accept(this);
  }
}

Element* FlattenedSetVisitor::getResult(){
  // for(int i = 0; i < _v.size(); i++) {
  //   set->add(_v.at(i));
  //   cout << _v.size() << endl;
  // }
  set->add(_fv[0]);
  return set;
}
