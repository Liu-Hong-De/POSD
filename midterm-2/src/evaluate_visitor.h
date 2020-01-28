#ifndef EVALUATE_VISITOR_H
#define EVALUATE_VISITOR_H

#include "visitor.h"
#include "element.h"

#include <vector>

using namespace std;

class EvaluateVisitor: public Visitor
{
    public:
        EvaluateVisitor();
        void visitInteger(Integer * i);
        void visitSet(Set * s);
        double getResult();
    private:
        vector<Element*> _v;
};
#endif
