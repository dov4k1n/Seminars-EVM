#include <iostream>
#include <vector>

int main() {
    FILE* input = fopen("main.cpp", "rt");
    if (input == NULL) {
        std::cout << "can't open file" << std::endl;
        return -1;
    }

    std::vector<char> charVector;
    char c;
    size_t n = 0;

    while ((c = fgetc(input)) != EOF) {
        charVector.push_back(c);
        n++;
    }

    fclose(input);

    for (size_t i = 0; i < n; i++) {
        std::cout << charVector[i];
    }
    std::cout << std::endl;

    return 0;
}