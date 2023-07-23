#include <stdio.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

typedef struct human {
    const char name;
    const char gender;
    const int age;
    int BMI;
};

void generate_human(FILE *human_list) {
    std::vector<char> name, gender;
    std::vector<int> age;
    std::vector<double> bmi;

    name.push_back(Ayzat);
    name.push_back("Ilya");
}

int main() {
    printf("Hi, I'm counting number of possible couples\n");
    printf("Enter 0 to input data, 1 to use random\n");
    
    int tmp;
    
    if (!(std::cin >> tmp)) {
        printf("wrong format\n");
        return -1;
    }

    FILE *human_list = fopen("human_list", "wt");
    if (tmp) {
        generate_human(human_list);
    }
    else {
        printf("Enter: name, gender, age, city, relationship status\n");
        
    }
}