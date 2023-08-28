/*
 * Program finds a string inside of Portable Executable 64 bit .exe file
 * and changes it to the one that user wants.
 * In my example, I change "Bill Gates" to "Ayzat Rizatdinov"
 * in a victim.cpp's .exe file, which prints
 * "this program is created by Bill Gates".
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void patch(std::fstream& file,
           const std::string& targetString,
           const std::string& replacementString) {
    std::vector<char> fileData(
        std::istreambuf_iterator<char>(file), {});

    // finding first occurence of targetString
    auto targetPos = std::search(
        fileData.begin(), fileData.end(),
        targetString.begin(), targetString.end());

    // replaces every occurence of targetString in file
    while (targetPos != fileData.end()) {
        std::copy(
            replacementString.begin(), replacementString.end(),
            targetPos);

        targetPos = std::search(
            targetPos + replacementString.size(),
            fileData.end(),
            targetString.begin(),
            targetString.end());
    }

    file.seekp(0, std::ios::beg);
    file.write(fileData.data(), fileData.size());

    std::cout << "replacementString complete." << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Need an exe file!" << std::endl;
		std::cout << argv[0] << " <file name>" << std::endl;
        return -1;
    }

    std::fstream file(
        argv[1], std::ios::in | std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::cout << "Enter the target string: ";
    std::string targetString;
    std::getline(std::cin, targetString);

    std::cout << "Enter the replacementString string: ";
    std::string replacementString;
    std::getline(std::cin, replacementString);

    patch(file, targetString, replacementString);

    file.close();

    return 0;
}