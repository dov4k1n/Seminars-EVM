#include "vector.h"

using std::cout;
using std::endl;
using std::cin;

int main() {
    Vector<int> vector;
    vector.push_back(10);
    vector.push_back(5);
    vector.push_back(8);
    vector.push_back(2);
    vector.push_back(7);

    cout << vector << endl;
    while (cin >> vector) cout << vector << endl;
    cout << endl;

    // vector.sort();

    // std::cout << "Sorted Vector: ";
    // for (size_t i = 0; i < vector.getSize(); ++i) {
    //     std::cout << vector[i] << " ";
    // }
    // std::cout << std::endl;

    return 0;
}