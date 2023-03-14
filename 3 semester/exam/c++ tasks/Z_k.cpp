#include <iostream>

const int MyPrime = 17;

class Zp {
  public:
    int value;

    Zp():
      value(0)
    {}

    Zp(int value):
      value(value)
    {
      value %= MyPrime;
      if (value < 0) value += MyPrime;
    }

    Zp operator=(Zp& other) const {
      other.value = value;
      return other;
    }

    Zp operator+(const Zp& other) const {
      Zp sum;
      sum.value = (this->value + other.value) % MyPrime;

      if (sum.value < 0)
        sum.value += MyPrime;

      return sum;
    }

    Zp& operator+=(const Zp& other) {
      value = (value + other.value) % MyPrime;

      if (value < 0)
        value += MyPrime;

      return *this;
    }

    Zp operator*(const Zp& other) const {
      Zp product;
      product.value = (this->value * other.value) % MyPrime;

      if (product.value < 0)
        product.value += MyPrime;

      return product;
    }

    Zp& operator*=(const Zp& other) {
      value = (value * other.value) % MyPrime;

      if (value < 0)
        value += MyPrime;

      return *this;
    }
};

int main(){
  Zp a(5), b(2);

  //std::cout << (a * b).value << std::endl;
  //std::cout << (a + b).value << std::endl;

  a=b;

  std::cout << a.value << std::endl;
  std::cout << b.value << std::endl;

  return 0;
}