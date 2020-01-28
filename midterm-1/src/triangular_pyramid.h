#ifndef TRIANGULAR_PYRAMID_H
#define TRIANGULAR_PYRAMID_H

#include <math.h>
#include "solid.h"

class TriangularPyramid: public Solid
{
public:
  TriangularPyramid(double x1, double y1, double x2, double y2, double x3, double y3, double height): _x1(x1), _y1(y1), _x2(x2), _y2(y2), _x3(x3), _y3(y3), _height(height)
  {
    if (isIsoscelesTriangle()==false) {
      throw std::string("Bottom is not a Triangle!");
    }
  }
  double bottomArea() const
  {
    double s = (l1 + l2 + l3) / 2;
    return sqrt(s * (s - l1) * (s - l2) * (s - l3));
  }

  double volume() const {
    return bottomArea() * _height / 3;
  }

  bool isIsoscelesTriangle()
  {
    if ((_x1==_x2 && _y1==_y2) || (_x3==_x2 && _y3==_y2) || (_x1==_x3 && _y1==_y3)) {
      return false;
    }
    else if (l1+l2==l3 || l1+l3==l2 || l2+l3==l1) {
      return false;
    }
    else if (l1!=l2 && l2!=l3 && l1!=l3) {
      return false;
    }
    else {
      return true;
    }
  }

private:
  double _x1;
  double _y1;
  double _x2;
  double _y2;
  double _x3;
  double _y3;
  double _height;
  double l1 = sqrt(pow(abs(_x2 - _x1), 2) + pow(abs(_y2 - _y1), 2));
  double l2 = sqrt(pow(abs(_x3 - _x2), 2) + pow(abs(_y3 - _y2), 2));
  double l3 = sqrt(pow(abs(_x1 - _x3), 2) + pow(abs(_y1 - _y3), 2));
};
#endif
