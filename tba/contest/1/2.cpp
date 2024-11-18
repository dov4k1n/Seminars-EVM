#include <iostream>

using std::cout, std::cin, std::endl;

int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    if (b <= c) {
      for (int i = b; i <= c; i++) {
        cout << i << " ";
      }
    } else if (b > c && b <= d) {
      for (int i = c; i <= b; i++) {
        cout << i << " ";
      }
    } else if (b > c && b > d) {
      for (int i = c; i <= d; i++) {
        cout << i << " ";
      }
    }

    cout << endl;

    return 0;
}