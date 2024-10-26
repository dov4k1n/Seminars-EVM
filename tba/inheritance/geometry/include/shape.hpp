#ifndef INCLUDE_SHAPE_HPP_
#define INCLUDE_SHAPE_HPP_

#include <iostream>

class Shape {
 public:
  virtual double length() const = 0;
  virtual double area() const = 0;
};

#endif // INCLUDE_SHAPE_HPP_