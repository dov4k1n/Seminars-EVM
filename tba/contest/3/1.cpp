#include <iostream>

using std::cout, std::cin, std::endl;

struct Point {
  int x = 0, y = 0;

  Point(int x = 0, int y = 0) : x(x), y(y) {}

  friend std::ostream& operator<<(std::ostream& out, const Point& p) {
    out << p.x << " " << p.y;
    return out;
  }

  friend std::istream& operator>>(std::istream& in, Point& p) {
    double x;
    double y;
    in >> x >> y;
    p.x = x;
    p.y = y;
    return in;
  }

  Point operator +(const Point& p) const { return Point(x + p.x, y + p.y); }
  Point operator *(const int& k) { return Point(x * k, y * k); }
  Point operator *(const Point& p) { return Point(x * p.x, y * p.y); }
  Point& operator ~() { x = 0; y = 0; return *this; }
  Point operator ++(int) { return Point(x * (-1), y); }
  Point operator --(int) { return Point(x, y * (-1)); }
};

int main() {
  Point a, b;
  cin >> a >> b;
  Point c = a + b;
  cout << c << endl;
  
  int k;
  cin >> k;
  cout << a * k << endl;
  cout << a * b << endl;
  cout << a-- << endl;
  cout << b++ << endl;
  cout << ~c << endl;
  return 0;
}