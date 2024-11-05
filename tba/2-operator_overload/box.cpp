#include <iostream>

class Box {
 private:
  double weight;
  double length;
  double width;
  double height;
  std::string color;

 public:
  Box(
    double weight = double(),
    double length = double(),
    double width = double(),
    double height = double(),
    std::string color = std::string()
  ) : 
    weight(weight),
    length(length),
    width(width),
    height(height),
    color(color)
  {}

  double get_weight() const { return weight; }
  std::string get_color() const { return color; }
  
  void set_color(const std::string& new_color) { color = new_color; }

  double get_volume() const { return length * width * height; }
  
  std::string is_hard() const { return weight > 100 ? "Hard" : "Not hard"; }
  
  bool is_harder_than(const Box& other) const { 
    return weight > other.get_weight() ? true : false;
  }

  double operator +(const Box& other) const { 
    return weight + other.get_weight();
  }

  void operator *(Box& other) const { other.set_color(color); }

  Box& operator ++() { 
    weight++;
    return *this;
  }

  Box operator ++(int) { return Box(++(*this)); }

  bool operator &&(const Box& other) const { 
    return (weight > 100 && other.get_weight() > 100) ? true : false;
  }

  // friend std::ostream& operator<<(std::ostream& out, const Box& box) {
  //   out << box.get_weight();
  //   return out;
  // }
};

int main() {
  Box one = Box(10, 2, 3, 5, "blue");
  Box two = Box(200, 10, 20, 30, "black");
  
  std::cout << "Box one weight: " << one.get_weight() << std::endl;
  std::cout << "Box two weight: " << two.get_weight() << std::endl << std::endl;

  std::cout << "Box one is hard? " << one.is_hard() << std::endl;
  std::cout << "Box two is hard? " << two.is_hard() << std::endl << std::endl;
  
  std::cout << "Box one is harder than Box two – " << one.is_harder_than(two) << std::endl;
  std::cout << "Box two is harder than Box one – " << two.is_harder_than(one) << std::endl << std::endl;
  
  std::cout << "(Box one + Box two).weight: " << (one + two) << std::endl << std::endl;
  
  std::cout << "Box one color: " << one.get_color() << std::endl;
  std::cout << "Box two color: " << two.get_color() << std::endl;
  std::cout << "painting..." << std::endl;
  one * two;
  std::cout << "Box one color: " << one.get_color() << std::endl;
  std::cout << "Box two color: " << two.get_color() << std::endl << std::endl;
  
  std::cout << "Box one weight: " << one.get_weight() << std::endl;
  std::cout << "increasing weight..." << std::endl;
  one++;
  std::cout << "Box one weight: " << one.get_weight() << std::endl << std::endl;
  
  std::cout << "Are Box one and Box two both weigh more than 100? " << (one && two) << std::endl << std::endl;
  
  std::cout << std::endl;

  return 0;
}