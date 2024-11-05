#ifndef INCLUDE_POINT_HPP_
#define INCLUDE_POINT_HPP_

#include <iostream>
#include "shape.hpp"

class Point : public Shape {
 private:
  double x, y;

 public:
  Point(
    double x = double(), 
    double y = double()
  ) : 
    x(x), 
    y(y) 
  {}

  double getX() const { return x; }
  double getY() const { return y; }
  void setX(const double& newX) { x = newX; }
  void setY(const double& newY) { y = newY; }

  double length() const override {
    return 0;
  }

  double area() const override {
    return 0;
  }

  friend std::ostream& operator<<(std::ostream& out, const Point& point) {
    out << "(" << point.x << ", " << point.y << ")";
    return out;
  }
};

#endif // INCLUDE_POINT_HPP_