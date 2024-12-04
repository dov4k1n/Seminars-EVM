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
  int a, b;

  int t;
  cin >> t;
  while (t > 0) {
    int method, store;
    cin >> method >> store;
    
    if (method == 1) {
      switch (store) {
        case 1:
          s1.merge(s2);
          break;
        
        case 2:
          s2.merge(s1);
          break;
        
        default:
          break;
      }
    } else if (method == 2) {
      string product;
      cin >> product;
      
      switch (store) {
        case 1:
          s1.merge(s2, product);
          break;
        
        case 2:
          s2.merge(s1, product);
          break;
        
        default:
          break;
      }
    }

    t--;
  }

  s1.print();
  s2.print();

  return 0;
}