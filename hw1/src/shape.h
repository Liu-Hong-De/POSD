#ifndef SHAPE_H
#define SHAPE_H

#include <string>

using namespace std;
class Shape
{
public:
  virtual double area() const = 0;
  virtual double perimeter() const = 0;
  virtual string getDetails() const = 0;
};
#endif
