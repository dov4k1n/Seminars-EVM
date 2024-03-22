#include "vector.h"
#include <limits>

using std::cout;
using std::endl;
using std::cin;
using std::string;

int main() {
    Vector<int> intVector1;
    Vector<int> intVector2;
    Vector<string> stringVector;

    int intElement;
    while (true) {
        cout << "Enter a number for intVector1 (enter -1 to stop): ";

        if (!(cin >> intElement)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        intVector1.push_back(intElement);

        if (intElement == -1) {
            intVector1.pop_back();
            break;
        }
    }

    while (true) {
        cout << "Enter a number for intVector2	(enter -1 to stop): ";

        if (!(cin >> intElement)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        intVector2.push_back(intElement);

        if (intElement == -1) {
            intVector2.pop_back();
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

    cout << endl << intVector1 << endl << intVector2 << endl << stringVector << endl;

    cout << endl;
    if (intVector1 <= intVector2) 
	    cout << "intVector1 <= intVector2" << endl;
    if (intVector1 < intVector2)
	    cout << "intVector1 < intVector2" << endl; 
    if (intVector1 >= intVector2)
            cout << "intVector1 >= intVector2" << endl;
    if (intVector1 > intVector2)
            cout << "intVector1 > intVector2" << endl;
    if (intVector1 == intVector2)
            cout << "intVector1 == intVector2" << endl;
    if (intVector1 != intVector2)
            cout << "intVector1 != intVector2" << endl;

    Vector<Vector<int>> vectorVector;
    vectorVector.push_back(intVector1);
    vectorVector.push_back(intVector2);

    cout << endl << vectorVector << endl;
    
    intVector1.sort();
    intVector2.sort();
    stringVector.sort();
    vectorVector.sort();

    cout << endl << "sorted: " << endl;
    cout << endl << intVector1 << endl << intVector2 << endl << stringVector << endl << vectorVector << endl;

    vectorVector.pop_back();
    cout << endl << vectorVector << endl;

    return 0;
}