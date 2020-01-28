#ifndef NULLITERATOR_H
#define NULLITERATOR_H

class NullIterator:public Iterator
{
  public:
    void first(){
      //throw string "no child member"
      throw(std::string("no child member"));
    }
    Node* currentItem(){
      //throw string "no child member"
      throw(std::string("no child member"));
    }
    void next() {
      //throw string "no child member"
      throw(std::string("no child member"));
    }
    bool isDone(){
      return true;
    }
};
#endif
