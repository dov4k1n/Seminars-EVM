#include <iostream>

using std::cout, std::cin, std::endl;

struct Point {
  long x = 0, y = 0;

  Point(long x = 0, long y = 0) : x(x), y(y) {}

  friend std::ostream& operator<<(std::ostream& out, const Point& p) {
    out << p.x << " " << p.y;
    return out;
  }

  friend std::istream& operator>>(std::istream& in, Point& p) {
    long x;
    long y;
    in >> x >> y;
    p.x = x;
    p.y = y;
    return in;
  }

  Point operator +(const Point& p) const { return Point(x + p.x, y + p.y); }
};

int main() {
  Point a, b;
  cin >> a >> b;
  Point c = a + b;
  cout << c << endl;
}