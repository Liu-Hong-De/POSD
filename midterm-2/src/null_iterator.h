#ifndef NULLITERATOR_H
#define NULLITERATOR_H
#include <string>
#include "iterator.h"

class NullIterator:public Iterator
{
  public:
    void first(){
      //throw string "no child member"
      throw(std::string("No child member!"));
    }
    Element* currentItem(){
      //throw string "no child member"
      throw(std::string("No child member!"));
    }
    void next() {
      //throw string "no child member"
      throw(std::string("No child member!"));
    }
    bool isDone(){
      throw(std::string("No child member!"));
    }
};
#endif
