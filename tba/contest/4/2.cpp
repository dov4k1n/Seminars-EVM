#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using std::cout, std::cin, std::endl, std::string, std::vector;

struct Product {
  string name;
  int price;
  int count;
};

struct Store {
  string owner;
  int balance;
  vector<Product> products;

  Store() {
    cin >> owner;
    cin >> balance;
    products.resize(6);
    for (Product& p : products) {
      cin >> p.name;
      cin >> p.price;
      cin >> p.count;
    }
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

  // includes the case when products has duplicates
  void merge(Store& b) {
    for (Product& p : products) {
      auto b_p = b.products.begin();

      while (b_p != b.products.end()) {
        if ((*b_p).name == p.name) {
          p.count += (*b_p).count;
          (*b_p).count = 0;
        }

        b_p = std::find_if(
          b_p + 1,
          b.products.end(),
          [&](const Product& product) {
            return product.name == p.name;
          }
        );
      }      
    }
  }

/*
Apple 10000
IPHONE 1 1
two 2 2
three 3 3
four 4 4
five 5 5
six 6 6
Xiaomi 1000
REDMI 1 1
two 2 2
three 3 3
notfour 4 4
five 0 10
six 100 100
*/

  void merge(Store& b, const string& p_name) {
    auto tmp = b.products.begin();
    while (tmp != b.products.end()) {
      if ((*tmp).name != p_name) tmp++;
      else break;
    }
    if (tmp == b.products.end()) return;

    for (Product& p : products) {
      if (p.name == p_name) {
        p.count += (*tmp).count;
        (*tmp).count = 0;
      }
    }
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

  int t;
  cin >> t;
  string query;
  string method;
  string store;
  string product;
  std::istringstream query_s;
  while (t > 0) {
    std::getline(std::cin, query);
    query_s.str() = query;
    std::getline(query_s, method, ' ');
    std::getline(query_s, store, ' ');

    if (method == "1") {
      switch (store) {
        case "1":
          s1.merge(s2);
          break;
        case "2":
          s2.merge(s1);
          break;
        default:
          break;
      }
    } else {
      std::getline(query, product, ' ');
      switch (store) {
        case "1":
          s1.merge(s2, product);
          break;
        case "2":
          s2.merge(s1, product);
          break;
        default:
          break;
      }
    }

    t--;
  }

  return 0;
}