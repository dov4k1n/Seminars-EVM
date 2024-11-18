#include <iostream>
#include <vector>

using std::cout, std::cin, std::endl, std::vector;

void print(const vector<int>& vect) {
  for (const int& v : vect) cout << v << " ";
  cout << endl;
}

int sum_even(const vector<int>& vect, const int& i) {
  int result = 0;
  for (int j = 0; j <= i; j++) {
    if (vect[j] % 2 == 0) result += vect[j];
  }
  return result;
}

int sum_odd(const vector<int>& vect, const int& i) {
  int result = 0;
  for (int j = 0; j <= i; j++) {
    if (vect[j] % 2 == 1) result += vect[j];
  }
  return result;
}

int max(const int& a, const int& b) {
  return a < b ? b : a;
}

int main() {
    int n;
    cin >> n;

    vector<int> vect1(n);
    for (int& v : vect1) cin >> v;
    vector<int> vect2(n);
    for (int& v : vect2) cin >> v;

    vector<int> result(n);

    for (int i = 0; i < n; i++) {
      result[i] = max(sum_even(vect1, i), sum_odd(vect2, i));
    }

    print(result);

    return 0;
}