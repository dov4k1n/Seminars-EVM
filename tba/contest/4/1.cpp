#include <iostream>
#include <vector>

using std::cout, std::cin, std::endl, std::string, std::vector;

struct Product {
  string name;
  int price;
  int count;

  Product() {
    cin >> name;
    cin >> price;
    cin >> count;
  }
};

struct Store {
  string owner;
  int balance;
  vector<Product> products;

  Store() {
    cin >> owner;
    cin >> balance;
    products.resize(6);
  }

  void add_funds(const int& count) { balance += count; }
  void withdraw_funds(const int& count) {
    if (balance - count >= 0) balance -= count;
  }

  void print() {
    cout
      << owner << " " << balance << endl
      << "-----" << endl;
    
    for (const Product& p : products) {
      cout << p.name << " cost: " << p.price << " (" << p.count << " left)" << endl;
    }

    cout << "-----" << endl;
  }
};

int main() {
  Store s1, s2;
  s1.print();
  int a, b;
  cin >> a >> b;
  s2.add_funds(a);
  s2.withdraw_funds(b);
  s2.print();

  return 0;
}