#include <iostream>
#include <list>
#include <iterator>
#include <vector>
 
std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
{
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}

/*int main() {
    std::vector<int> v{ 3, 1, 4, 5, 6 };
 
    auto vi = v.begin();
    std::advance(vi, 2);
    std::cout << *vi << ' ';
 
    vi = v.end();
    std::advance(vi, -2);
    std::cout << *vi << '\n';

    return 0;
}*/

int main () {
    std::list<int> list1 = { 1, 2, 3, 4, 5 };
    std::list<int> list2 = { 10, 20, 30, 40, 50 };
 
    auto it = list1.begin();
    std::advance(it, 2);
 
    list1.splice(it, list2);
 
    std::cout << "list1: " << list1 << "\n";
    std::cout << "list2: " << list2 << "\n";
 
    list2.splice(list2.begin(), list1, it, list1.end());
 
    std::cout << "list1: " << list1 << "\n";
    std::cout << "list2: " << list2 << "\n";

    list1.erase(list1.begin());
    std::cout << "list1: " << list1 << "\n";

    std::list<int>::iterator Iter;
    Iter = std::next(list1.begin());
    std::cout << "Iter = " << *Iter << std::endl;

    list1.erase(Iter);
    std::cout << "list1: " << list1 << "\n";

    return 0;
}