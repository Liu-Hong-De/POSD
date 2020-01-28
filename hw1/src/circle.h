#ifndef CIRCLE_H
#define CIRCLE_H

#include <math.h>
#include <sstream>
using namespace std;
class Circle: public Shape
{
public:
  Circle(double r):_r(r)
  {

  }

  double area() const
  {
    return M_PI * _r * _r;
  }

  double perimeter() const
  {
    return 2 * M_PI * _r;
  }

  string getDetails() const {
    stringstream ss;
    ss << "circle" << " " << _r;
    return ss.str();
  }
private:
  double _r;
};
#endif
