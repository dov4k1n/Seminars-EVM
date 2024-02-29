#include "vector.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;

int main() {
    Vector<int> intVector;
    Vector<string> stringVector;

    int intElement;
    while (true) {
        cout << "Enter a number (enter -1 to stop): ";

        if (!(cin >> intElement)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        intVector.push_back(intElement);

        if (intElement == -1) {
            intVector.pop_back();
            break;
        }
    }

    string stringElement;
    while (true) {
        cout << "Enter a string (enter \"exit\" to stop): ";

        if (!(cin >> stringElement)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a string." << endl;
            continue;
        }

        stringVector.push_back(stringElement);

        if (stringElement == "exit") {
            stringVector.pop_back();
            break;
        }
    }

    intVector.print();
    stringVector.print();

    intVector.sort();
    stringVector.sort();

    cout << endl << "sorted: " << endl;

    intVector.print();
    stringVector.print();

    return 0;
}