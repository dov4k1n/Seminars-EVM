#include <iostream>
#include <list>

std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list) {
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}

std::list<int> gen_rand_list(const int& list_len, const int& list_range) {
  std::list<int> my_ret;
  for (int i = 0; i < list_len; i++)
    my_ret.push_back(rand() % list_range);
  return my_ret;
}

void clear_repeatitions(std::list<int>& initial_list) {
  std::list<int>::iterator Iter, Iter2, tmp;

  for (Iter = initial_list.begin(); Iter != initial_list.end(); Iter++ ) {
    Iter2 = std::next(Iter);
    while (Iter2 != initial_list.end()) {
      tmp = Iter2;
      Iter2++;
      if (*tmp == *Iter) {
        initial_list.erase(tmp);
      }
    }
  }
}

int main() {
  std::cout << "enter list length and range of elements" << std::endl;

  int list_len, list_range;

  std::cin >> list_len >> list_range;
  
  std::list<int> initial_list = gen_rand_list(list_len, list_range);

  std::cout << "initial list is: " << initial_list << std::endl;

  clear_repeatitions(initial_list);

  std::cout << "changed list is: " << initial_list << std::endl;
  std::cout << "previous length is " << list_len << ", " << "new length is " << initial_list.size()
            << "."<< std::endl;

  return 0;
}