#include <iostream>
#include <vector>

using std::cout, std::cin, std::endl, std::vector, std::string;

class Box {
 private:
  int length;
  int width;
  int height;
  int max_cap;
  int cur_cap;
  string material;

 public:
  Box(
    int length,
    int width,
    int height,
    int max_cap,
    int cur_cap,
    string material
  ) :
    length(length),
    width(width),
    height(height),
    max_cap(max_cap),
    cur_cap(cur_cap),
    material(material)
  { }

  Box() {
    cin >> length;
    cin >> width;    
    cin >> height;
    cin >> max_cap;
    cin >> cur_cap;
    cin >> material;
  }

  void print() {
    cout 
      << length << " " 
      << width << " "
      << height << " "
      << max_cap << " "
      << cur_cap << " "
      << material << endl;
  }

  void free() { cur_cap = 0; }

  void put_weight(const int& _weight) {
    if (cur_cap + _weight <= max_cap) 
      cur_cap = cur_cap + _weight;
  }

  int weight() const { return cur_cap; }

  void put_weight(const Box& b) {
    if (cur_cap + b.weight() <= max_cap)
      cur_cap += b.weight();
  }

  void multiply_weight(const int& n) {
    if (cur_cap * n > max_cap)
      cur_cap = max_cap;
    else
      cur_cap *= n;
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
  
  return 0;
}