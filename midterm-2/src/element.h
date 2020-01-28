#ifndef ELEMENT_H
#define ELEMENT_H

#include "visitor.h"
#include "iterator.h"
#include "null_iterator.h"

class Element{
public:
    Element(){
    }

    virtual ~Element() {}

    virtual void add(Element * s) = 0;

    virtual int size()=0;

    virtual std::string toString() = 0;

    virtual Iterator * createIterator() = 0;

    virtual void setOperator(char ope) = 0;

    virtual void accept(Visitor * fsv) = 0;

};
#endif
