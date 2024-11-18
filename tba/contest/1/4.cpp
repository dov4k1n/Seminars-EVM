#include <iostream>
#include <math.h>

using std::cout, std::cin, std::endl;

int perf_sq_less(const int& a) {
  int result = 1;
  int i = 2;

  while (i * i <= a) {
    result = i * i;
    i++;
  }

  return result;
}

int perf_sq_greater(const int& b) {
  int i = 1;

  while (i * i < b) {
    i++;
  }

  int result = i * i;

  return result;
}

int main() {
    int a, b;
    cin >> a >> b;

    int k1 = perf_sq_less(a);
    int k2 = perf_sq_greater(b);
    // cout << "k1, k2: " << k1 << " " << k2 << endl;

    if (a - k1 > k2 - b) {
      cout << 1;
    } else if (k2 - b > a - k1) {
      cout << 2;
    } else {
      cout << 0;
    }

    cout << endl;

    return 0;
}