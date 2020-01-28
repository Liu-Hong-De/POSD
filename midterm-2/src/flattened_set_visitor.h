#ifndef FLATTENED_SET_VISITOR_H
#define FLATTENED_SET_VISITOR_H

#include "visitor.h"
#include "element.h"

#include <vector>

using namespace std;

class FlattenedSetVisitor: public Visitor
{
    public:
        FlattenedSetVisitor();
        void visitInteger(Integer * i);
        void visitSet(Set * s);
        Element* getResult();
    private:
        vector<Element*> _fv;
        Set *set;
};
#endif
