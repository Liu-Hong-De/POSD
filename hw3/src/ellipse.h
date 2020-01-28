#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"
#include <math.h>
#include <sstream>

using namespace std;

class Ellipse: public Shape
{
public:
  Ellipse(double semiMajorAxes,double semiMinorAxes): _semiMajorAxes(semiMajorAxes), _semiMinorAxes(semiMinorAxes)
  {

  }

  double area() const
  {
    return M_PI * _semiMajorAxes * _semiMinorAxes;
  }

  double perimeter() const
  {
    return 2 * M_PI * _semiMinorAxes + 4 * (_semiMajorAxes - _semiMinorAxes);
  }

  double sumOfSquares() const
  {
    return pow(area(), 2) + pow(perimeter(), 2);
  }

  string getDetails() const {
    stringstream ss;
    ss << "ellipse" << " " << _semiMajorAxes << " " << _semiMinorAxes;
    return ss.str();
  }

private:
  double _semiMajorAxes;
  double _semiMinorAxes;
};
#endif
