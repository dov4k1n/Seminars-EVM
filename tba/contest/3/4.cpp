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
  Point operator *(const long& k) { return Point(x * k, y * k); }
  Point operator *(const Point& p) { return Point(x * p.x, y * p.y); }
  Point& operator ~() { x = 0; y = 0; return *this; }
  Point operator ++(int) { return Point(x * (-1), y); }
  Point operator --(int) { return Point(x, y * (-1)); }

  bool operator <(const Point& p) const {
    if (abs(x) + abs(y) < abs(p.x) + abs(p.y))
      return true;
    return false;
  }

  bool operator <=(const Point& p) const {
    if (p < *this)
      return false;
    return true;
  }

  bool operator >(const Point& p) const {
    if (p < *this)
      return true;
    return false;
  }

  bool operator >=(const Point& p) const {
    if (*this < p)
      return false;
    return true;
  }

  bool operator ==(const Point& p) const {
    if (*this < p || p < *this)
      return false;
    return true;
  }

  bool operator !=(const Point& p) const {
    if (*this < p || p < *this)
      return true;
    return false;
  }

  bool operator ||(const Point& p) const {
    if (x == 0 || y == 0 || p.x == 0 || p.y == 0)
      return true;
    return false;
  }

  bool operator &&(const Point& p) const {
    if (x == 0 && p.x == 0 || y == 0 && p.y == 0)
      return true;
    return false;
  }

  bool operator %(const Point& p) const {
    if (*this || p)
      return false;
    if (x > 0 && p.x < 0 || y > 0 && p.y < 0)
      return false;
    if (x < 0 && p.x > 0 || y < 0 && p.y > 0)
      return false;
    return true;
  }

  double operator^(const Point& p) const {
    if (x == p.x && y == p.y)
      return 0.0;
    return abs(x * p.y - p.x * y) / 2.0;
  }
};

int main() {
  Point a, b, c;
  cin >> a >> b;
  cout <<
    (a || b) << " " <<
    (a && b) << " " <<
    (a % b) << " " <<
    (a ^ b) <<
  endl;
}