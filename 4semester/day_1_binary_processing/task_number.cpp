#include <iostream>

int main() {
  int k;
  for (k = 1; k < 17; k++) {
    std::cout << k << ". " << (k*7+3)%20+1 << std::endl;
  }
}