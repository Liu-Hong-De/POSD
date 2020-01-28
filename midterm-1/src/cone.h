#ifndef CONE_H
#define CONE_H

#include <math.h>
#include "solid.h"

class Cone: public Solid
{
public:
  Cone(double x1,double y1,double x2,double y2, double height):_x1(x1), _y1(y1), _x2(x2), _y2(y2), _height(height)
  {
    if(_radius == 0) {
      throw(std::string("Bottom is not a Circle!"));
    }
  }

  double bottomArea() const
  {
    return _radius * _radius * M_PI;
  }

  double volume() const
  {
    return bottomArea() * _height / 3;
  }

private:
  double _x1;
  double _y1;
  double _x2;
  double _y2;
  double _height;
  double _radius = (sqrt(pow(abs(_x2-_x1), 2) + pow(abs(_y2-_y1), 2))) / 2;
};
#endif
