#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>

typedef struct human {
    //char name;
    std::string name;
    int BMI;
};

std::vector<human> gen_hum(const int& amountof_human) {
	std::vector<human> myret;
	human tmp;

	//new char names[7] = {'Ayzat','Ayrat','Artem','Ilya','Ivan','Rasul','Vlad'}; tak ne rabotaet
    std::vector<std::string> names = {"Ayzat","Ayrat","Artem","Ilya","Ivan","Rasul","Vlad"};

    //char* names[] = {"Ayzat", "Ayrat"}; tak tozhe mojno

	for (int i = 0; i < amountof_human; i++) {
		tmp.name = names[rand() % 7];
		tmp.BMI = 15 + (rand() % 26);
		myret.push_back(tmp);
	}
	return myret;
}

int main() {
    printf("Hi, I print generated humans and their BMIs\n");
    printf("Enter amount of human you want to generate\n");
    
	int amountof_human;
    if (!(std::cin >> amountof_human) || amountof_human < 1) {
        printf("wrong format\n");
        return -1;
    }
	std::vector<human> generated_humans = gen_hum(amountof_human);

	for (auto& v : generated_humans) {
        std::cout << v.name << v.BMI << " ";
    }
    std::cout << std::endl;

    return 0;
}