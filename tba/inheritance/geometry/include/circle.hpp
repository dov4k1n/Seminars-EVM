#ifndef INCLUDE_CIRCLE_HPP_
#define INCLUDE_CIRCLE_HPP_

#include <numbers>
#include "point.hpp"

class Circle : public Shape {
 private:
  Point center;
  double radius;

 public:
  Circle(
    const Point& center = Point(), 
    double radius = double()
  ) : 
    center(center), 
    radius(radius) 
  {}

  double length() const override {
    return 2 * std::numbers::pi_v<double> * radius;  
  }

  double area() const override {
    return std::numbers::pi_v<double> * radius * radius;
  }

  friend std::ostream& operator<<(std::ostream& out, const Circle& circle) {
    out << "center " << circle.center << ", radius " << circle.radius;
    return out;
  }
};

#endif // INCLUDE_CIRCLE_HPP_