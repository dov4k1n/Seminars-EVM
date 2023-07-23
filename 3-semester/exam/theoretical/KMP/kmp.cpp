#include <iostream>
#include <vector>

std::vector<int> compute_prefix_function(const std::string& P) {
  int m = (int)P.length();
  std::vector<int> prefix_array(m);
  int k = 0;
  prefix_array[0] = 0;

  for (int q = 1; q < m; q++) {
    while (k > 0 && P[k+1] != P[q])
      k = prefix_array[q];
    if (P[k+1] == P[q])
      k++;
    prefix_array[q] = k;
  }

  return prefix_array;
}