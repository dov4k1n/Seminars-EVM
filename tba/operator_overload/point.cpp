#include <iostream>
#include <math.h>

class Point {
 private:
  double x;
  double y;
  std::string color;

 public:
  Point(
    double x = double(),
    double y = double(),
    std::string color = std::string()
  ) :
    x(x),
    y(y),
    color(color)
  { }

  Point(double& _x, double& _y) {
    x = _x;
    y = _y;
    color = "black";
  }

  double get_x() const { return x; }
  double get_y() const { return y; }
  std::string get_color() const { return color; }
  
  void set_x(const double& new_x) { x = new_x; }
  void set_y(const double& new_y) { y = new_y; }
  void set_color(const std::string& new_color) { color = new_color; }

  Point operator +(const Point& other) const {
    return Point(x + other.get_x(), y + other.get_y(), color);
  }

  void operator *(const int& scalar) { x *= scalar; y *= scalar; }

  double operator ^(const Point& other) {
    return sqrt(
      pow(x - other.get_x(), 2) + pow(y - other.get_y(), 2)
    );
  }

  friend std::ostream& operator<<(std::ostream& out, const Point& point) {
    out << "(" << point.get_x() << ", " << point.get_y() << ") " << point.get_color();
    return out;
  }

  // friend std::istream& operator>>(std::istream& in, Point& point) {
  //   double x
  //   double y
  //   std::string
  //   in >> x;
  //   in >> y;
  //   in >> color;
  //   return in;
  // }

  bool operator ||(const Point& other) const {
    bool x_sign_match = x * other.get_x() >= 0;
    bool y_sign_match = y * other.get_y() >= 0;
    
    return x_sign_match && y_sign_match ? true : false;
  }
};

int main() {
  Point blue(1, 2, "blue");
  Point red(10, 16, "red");
  Point black(-1, 10); // black
  Point yellow(-1, -6, "yellow");

  std::cout << "Points:" << std::endl;
  std::cout << blue << std::endl << red << std::endl << black << std::endl << yellow << std::endl << std::endl;

  std::cout << "Sum of Points blue and red: " << blue + red << std::endl << std::endl;

  std::cout << "Scaling Point black by 10" << std::endl;
  black * 10;
  std::cout << black << std::endl << std::endl;

  std::cout << "Distance between blue and red Points: " << (blue ^ red) << std::endl << std::endl;

  std::cout << "Are blue and red in the same quarter?: " << (blue || red) << std::endl;
  std::cout << "Are blue and black in the same quarter?: " << (blue || black) << std::endl;
  std::cout << "Are blue and yellow in the same quarter?: " << (blue || yellow) << std::endl;
  std::cout << "Are red and black in the same quarter?: " << (red || black) << std::endl;
  std::cout << "Are red and yellow in the same quarter?: " << (red || yellow) << std::endl;
  std::cout << "Are black and yellow in the same quarter?: " << (black || yellow) << std::endl;

  return 0;
}