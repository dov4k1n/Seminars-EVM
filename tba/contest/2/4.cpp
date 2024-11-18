#include <iostream>
#include <vector>

using std::cout, std::cin, std::endl, std::vector, std::string;

class Box {
 private:
  int _length;
  int _width;
  int _height;
  int _max_cap;
  int _cur_cap;
  string _material;

 public:
  Box(
    int _length,
    int _width,
    int _height,
    int _max_cap,
    int _cur_cap,
    string _material
  ) :
    _length(_length),
    _width(_width),
    _height(_height),
    _max_cap(_max_cap),
    _cur_cap(_cur_cap),
    _material(_material)
  { }

  Box() {
    cin >> _length;
    cin >> _width;    
    cin >> _height;
    cin >> _max_cap;
    cin >> _cur_cap;
    cin >> _material;
  }

  void print() {
    cout 
      << _length << " " 
      << _width << " "
      << _height << " "
      << _max_cap << " "
      << _cur_cap << " "
      << _material << endl;
  }

  void free() { _cur_cap = 0; }

  void put_weight(const int& weight) {
    if (_cur_cap + weight <= _max_cap) 
      _cur_cap = _cur_cap + weight;
  }

  int weight() const { return _cur_cap; }

  void put_weight(const Box& b) {
    if (_cur_cap + b.weight() <= _max_cap)
      _cur_cap += b.weight();
  }

  void multiply_weight(const int& n) {
    if (_cur_cap * n > _max_cap)
      _cur_cap = _max_cap;
    else
      _cur_cap *= n;
  }

  int length() const { return _length; }
  int width() const { return _width; }
  int height() const { return _height; }

  bool can_hold(const Box& b) {
    if (
      (b.length() <= _length) &&
      (b.width() <= _width) &&
      (b.height() <= _height) &&
      (b.weight() + _cur_cap <= _max_cap)
    ) return true;
    else
      return false;
  }

  bool is_cube() {
    if (
      (_length == _width) &&
      (_width == _height)
    ) return true;
    else
      return false;
  }
};

int main() {
  Box b1(100, 40, 60, 60, 10, "wood");
  Box b2;
  
  b1.print();
  cout << endl;
  b2.print();
  cout << endl;

  Box b3;
  
  int k;
  cin >> k;
  switch (k) {
    case 1:
      b1.free();
      break;
    case 2:
      b2.free();
      break;
    case 3:
      b3.free();
      break;
    default:
      break;
  }

  int k2, aw;
  cin >> k2 >> aw;
  switch (k2) {
    case 1:
      b1.put_weight(aw);
      break;
    case 2:
      b2.put_weight(aw);
      break;
    case 3:
      b3.put_weight(aw);
      break;
    default:
      break;
  }

  b1.print();
  cout << endl;
  b2.print();
  cout << endl;
  b3.print();
  cout << endl;

  b2.put_weight(b3);
  int n;
  cin >> k >> n;
  switch (k) {
    case 1:
      b1.multiply_weight(n);
      break;
    case 2:
      b2.multiply_weight(n);
      break;
    case 3:
      b3.multiply_weight(n);
      break;
    default:
      break;
  }

  b1.print();
  cout << endl;
  b2.print();
  cout << endl;
  b3.print();
  cout << endl;

  cout << b3.can_hold(b2) << " " << b2.is_cube() << endl;
  
  return 0;
}