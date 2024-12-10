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
  
};

int main() {
  Box b1(100, 40, 60, 60, 10, "wood");
  Box b2;
  
  b1.print();
  cout << endl;
  b2.print();
  
  return 0;
}