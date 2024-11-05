#ifndef INCLUDE_LINE_HPP_
#define INCLUDE_LINE_HPP_

#include <cmath>
#include "point.hpp"

class Line : public Shape {
 private:
  Point start, end;

 public:
  Line(
    const Point& start = Point(), 
    const Point& end = Point()
  ) : 
    start(start), 
    end(end) 
  {}

  double get_startX() const { return start.getX(); }
  double get_startY() const { return start.getY(); }
  void set_startX(const double& newX) { start.setX(newX); }
  void set_startY(const double& newY) { start.setY(newY); }

  double get_endX() const { return end.getX(); }
  double get_endY() const { return end.getY(); }
  void set_endX(const double& newX) { end.setX(newX); }
  void set_endY(const double& newY) { end.setY(newY); }

  double length() const override {
    return std::sqrt(
      std::pow(end.getX() - start.getX(), 2) + 
      std::pow(end.getY() - start.getY(), 2)
    );
  }

  double area() const override {
    return 0;
  }

  friend std::ostream& operator<<(std::ostream& out, const Line& line) {
    out << line.start << " – " << line.end;
    return out;
  }
};

#endif // INCLUDE_LINE_HPP_