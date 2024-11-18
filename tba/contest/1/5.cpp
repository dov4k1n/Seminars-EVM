#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using std::cout, std::cin, std::endl, std::vector;

int div(const vector<int>& vect) {
  int res = -1;

  int prev_mid = -1;
  for (int i = 1; i < vect.size() - 1; i++) {
    int mid = vect[i];
    int left = vect[i-1];
    int right = vect[i+1];

    // cout << endl << "left, mid, right: " << left << " " << mid << " " << right << endl;

    bool mid_div_lr = (mid % left == 0) || (mid % right == 0);
    bool lr_div_mid = (left % mid == 0) && (right % mid == 0);
    
    // cout << "mid div lr: " << mid_div_lr << endl;
    // cout << "lr div mid: " << lr_div_mid << endl; 
    
    if (!mid_div_lr && lr_div_mid && mid > prev_mid) {
      res = i;
      // cout << "res: " << res << endl;
      prev_mid = mid;
    }
  }

  return res;
}

void print(const vector<int>& vect) {
  for (const int& v : vect) cout << v << " ";
  cout << endl;
}

void check() {
  std::srand(std::time(nullptr));
  vector<int> vect(12);
  for (int& v : vect) {
    v = std::rand() % 6 + 1;
  }

  print(vect);

  cout << div(vect) << endl;
}

int main() {
  int n;
  cin >> n;

  vector<int> vect(n);
  for (int& v : vect) cin >> v;

  cout << div(vect) << endl;
  // check();

  return 0;
}