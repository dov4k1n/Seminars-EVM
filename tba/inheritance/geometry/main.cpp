#include <iostream>

#include "include/shape.hpp"
#include "include/point.hpp"
#include "include/line.hpp"
#include "include/circle.hpp"

int main() {
  Point point;
  Line line;
  Circle circle;

  std::cout << point << std::endl;
  std::cout << line << std::endl;  
  std::cout << circle << std::endl << std::endl;

  std::cout << point.length() << std::endl;
  std::cout << line.length() << std::endl;
  std::cout << circle.length() << std::endl << std::endl;
  
  std::cout << point.area() << std::endl;
  std::cout << line.area() << std::endl;
  std::cout << circle.area() << std::endl << std::endl;

  Point point1(1, 2);
  Point point2(2, 4);
  Line line1(point1, point2);
  Circle circle1(point1, 1);

  std::cout << point1 << std::endl;
  std::cout << point2 << std::endl;
  std::cout << line1<< std::endl;
  std::cout << circle1<< std::endl << std::endl;

  std::cout << point1.length() << std::endl;
  std::cout << point2.length() << std::endl;
  std::cout << line1.length() << std::endl;
  std::cout << circle1.length() << std::endl << std::endl;
  
  std::cout << point1.area() << std::endl;
  std::cout << point2.area() << std::endl;
  std::cout << line1.area() << std::endl;
  std::cout << circle1.area() << std::endl << std::endl;

  return 0;
}