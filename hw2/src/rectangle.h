#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <sstream>
using namespace std;
class Rectangle: public Shape
{
public:
  Rectangle(double l, double w):_l(l), _w(w)
  {

  }

  double area() const
  {
    return _l * _w;
  }

  double perimeter() const
  {
    return 2 * (_l + _w);
  }

  double sumOfSquares() const
  {
    return pow(area(), 2) + pow(perimeter(), 2);
  }

  string getDetails() const {
    stringstream ss;
    ss << "rectangle" << " " << _l << " " << _w;
    return ss.str();
  }

private:
  double _l;
  double _w;
};
#endif
