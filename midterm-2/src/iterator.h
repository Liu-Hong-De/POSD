#ifndef ITERATOR_H
#define ITERATOR_H

class Element;
class Iterator{
public:
  virtual bool isDone()=0;
  virtual void first()=0;
  virtual void next()=0;
  virtual Element* currentItem()=0;
};
#endif
