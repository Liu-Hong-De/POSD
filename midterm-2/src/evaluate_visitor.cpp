#include "evaluate_visitor.h"
#include "integer.h"
#include "set.h"
#include "element.h"
#include "iterator.h"

#include <vector>
#include <string>
using namespace std;

EvaluateVisitor::EvaluateVisitor()
{

}

void EvaluateVisitor::visitInteger(Integer * i){
  _v.push_back(i);
}

void EvaluateVisitor::visitSet(Set * s){
  Iterator *it = s->createIterator();
  for (it->first(); !it->isDone(); it->next()) {
    it->currentItem()->accept(this);
  }
}

double EvaluateVisitor::getResult(){
  // Set set = new Set();
  // for(int i = 0; i < _v.size(); i++) {
  //   set.add(_v.at(i));
  // }
  // return &set;
}
