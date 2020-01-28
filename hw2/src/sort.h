#ifndef SORT_H
#define SORT_H

#include <string.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include "shape.h"

bool areaAscendingComparison(Shape* a, Shape* b);
bool areaDescendingComparison(Shape* a, Shape* b);

class AscendingComparison;
class DescendingComparison;

class Sort
{
    public:
      Sort(std::vector<Shape*>* v): _v(v){}

      void sortArea(std::function<bool (Shape*, Shape*)> compare) {
        std::sort(this->_v->begin(), this->_v->end(), compare);
      }

      void sortPerimeter(std::function<bool (Shape*, Shape*)> compare) {
        std::sort(this->_v->begin(), this->_v->end(), compare);
      }

      void sortSumOfSquares(std::function<bool (Shape*, Shape*)> compare) {
        std::sort(this->_v->begin(), this->_v->end(), compare);
      }

      int myQuick(std::vector<Shape*>::iterator iter, int beg, int end, std::function<bool (Shape* a, Shape* b)> compare)
      {
        int i = beg;
        int j = end;
        Shape *pivot = *(iter+(i + j) / 2);
        int temp;

        while (i <= j)
        {
          while (compare(*(iter+i), pivot))
            i++;
          while (compare(pivot, *(iter+j)))
            j--;
          if (i <= j)
          {
            swap(*(iter+i), *(iter+j));
            i++;
            j--;
          }
        }
        if (j > beg)
          myQuick(iter, beg, j, compare);
        if (i < end)
          myQuick(iter, i, end, compare);
      }


      void quickSort(std::function<bool (Shape* beg, Shape* end)> compare) {
        std::vector<Shape*>::iterator iter;
        iter = this->_v->begin();

        myQuick(iter, 0, this->_v->size()-1, compare);
      }

    private:
      std::vector<Shape*>* _v;
};

bool areaAscendingComparison(Shape* a, Shape* b) {
  return a->area() < b->area();
}

bool areaDescendingComparison(Shape* a, Shape* b) {
  return a->area() > b->area();
}

class AscendingComparison{
public:
  AscendingComparison(string a): _a(a)
      {
      }

      bool operator()(Shape* a, Shape* b)
      {
        if(_a=="area") {
          return a->area() < b->area();
        }
        else if(_a=="perimeter") {
          return a->perimeter() < b->perimeter();
        }
        else if(_a=="sumOfSquares") {
          return a->sumOfSquares() < b->sumOfSquares();
        }
      }

private:
  string _a;
};

class DescendingComparison{
public:
  DescendingComparison(string a): _a(a)
      {
      }

      bool operator()(Shape* a, Shape* b)
      {
        if(_a=="area") {
          return a->area() > b->area();
        }
        else if(_a=="perimeter") {
          return a->perimeter() > b->perimeter();
        }
        else if(_a=="sumOfSquares") {
          return a->sumOfSquares() > b->sumOfSquares();
        }
      }

private:
  string _a;
};

#endif
