// clck.ru/3EKFqp

#include <iostream>
#include <cmath>
#include <algorithm>

template <typename T>
struct Point {
  T x, y;

  Point(T x = T(), T y = T()) : x(x), y(y) {}
};

// 1
template <typename T>
T magn(const Point<T>& p) {
  return std::sqrt(p.x * p.x + p.y * p.y);
}

// 2
template <typename T>
T max(const T& a, const T& b) {
  return a < b ? b : a;
}

// 3
template <typename T>
size_t count_unique(const T& a, const T& b, const T& c) {
  size_t ans = 1;
  if (a != b && b != c) ans++;
  if (a != c) ans++;
  return ans;
}

// 4
template <typename T>
T sum(const T* arr, const size_t& n) {
  T ans = 0;
  for (size_t i = 0; i < n; i++) {
    ans += arr[i];
  }
  return ans;
}

// 5
template <typename T>
size_t count_eq(const T* arr, const size_t& n, const T& k) {
  T ans = 0;
  for (size_t i = 0; i < n; i++) {
    if (arr[i] == k) ans++;
  }
  return ans;
}

// 6
template <typename T>
size_t count_not_minmax(const T* arr, const size_t& n) {
  if (arr == nullptr) {
    return 0;
  }

  T ans = 0;
  T min = arr[0];
  T max = arr[0];

  for (size_t i = 0; i < n; i++) {
    if (arr[i] < min) min = arr[i];
    if (arr[i] > max) max = arr[i];
  }

  // std::cout << "min " << min << ", max " << max << std::endl;

  for (size_t i = 0; i < n; i++) {
    if ((arr[i] != min) && (arr[i] != max)) ans++;
  }

  return ans;
}

// 7
template <typename T>
void print_sorted(
  const T* arr1,
  const T* arr2,
  const size_t& n1,
  const size_t& n2
) {
  double* arr_unified = new double[n1 + n2];
  
  for (size_t i = 0; i < n1; i++) {
    arr_unified[i] = arr1[i];
  }
  
  for (size_t i = 0; i < n2; i++) {
    arr_unified[n1 + i] = arr2[i];
  }

  std::sort(arr_unified, arr_unified + n1 + n2);
  
  std::cout << std::endl;

  for (size_t i = 0; i < n1 + n2; i++) {
    std::cout << arr_unified[i] << " ";
  }

  std::cout << std::endl;
  
  delete[] arr_unified;
}

int main() {
  Point<double> a(3, 4);

  std::cout << "magn of (3, 4) is "<< magn(a) << std::endl;

  double x = 2.5;
  double y = 4.5;
  double z = 2.5;

  std::cout << "max of " << x << " and " << y << " is " << max(x, y) << std::endl;

  std::cout << "unique(" << x << ", " << y << ", " << z << ").size() is " << count_unique(x, y, z) << std::endl;

  std::cout << std::endl;
  size_t n = 10;
  double* arr_d = new double[n];
  for (size_t i = 0; i < n; i++) {
    std::cout << "arr1[" << i << "] = " << i << std::endl; 
    arr_d[i] = i;
  }

  std::cout << "sum from 0 to 9 is " << sum(arr_d, n) << std::endl;

  double k = 1;

  std::cout << "count equal to " << k << " is " << count_eq(arr_d, n, k) << std::endl;
  
  std::cout << "count not minmax is " << count_not_minmax(arr_d, n) << std::endl;

  std::cout << std::endl;
  size_t m = 5;
  double* arr_d2 = new double[m];
  for (size_t i = 0; i < m; i++) {
    std::cout << "arr2[" << i << "] = " << 3 * i + 7 % m << std::endl; 
    arr_d2[i] = 3 * i + 7 % m;
  }

  print_sorted(arr_d2, arr_d, m, n);
  
  delete[] arr_d;
  delete[] arr_d2;

  return 0;
}