/*
 * Program finds a string inside of Portable Executable 64 bit .exe file
 * and changes it to the one the user wants.
 * 
 * In my example, I change "Bill Gates" to "Ayzat Rizatdinov"
 * in a victim.cpp's .exe file, which prints
 * "this program is created by Bill Gates".
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

/*
 * Function loads every char from file in binary mode inside vector,
 * finds first occurence of user's target String,
 * replaces it with user's replacement String
 * and overwrites into the file modified chars from vector.
 */
void patch(
  std::fstream& file,
  const std::string& targetString,
  const std::string& replacementString
) {
  std::vector<char> fileData(
    std::istreambuf_iterator<char>(file), 
    {}
  );

  // finds first occurence of targetString
  auto targetPos = std::search(
    fileData.begin(), 
    fileData.end(),
    targetString.begin(), 
    targetString.end()
  );

  // replaces every occurence of targetString in file
  while (targetPos != fileData.end()) {
    std::copy(
      replacementString.begin(), 
      replacementString.end(),
      targetPos
    );

    targetPos = std::search(
      targetPos + replacementString.size(),
      fileData.end(),
      targetString.begin(),
      targetString.end()
    );
  }

  // seeks to the beginning of file and writes all data from modified vector
  file.seekp(0, std::ios::beg);
  file.write(fileData.data(), fileData.size());
}

/*
 * Main function takes as an argument name of the file that is
 * needed to be patched. Example of use after compilation
 * ".\a.exe target_file.exe".
 * 
 * In my example, I compile "g++ victim.cpp -o victim",
 * then compile "g++ change_string_data.cpp" in command line,
 * then type ".\a.exe victim.exe".
 * 
 * Before the patch, typing ".\victim.exe" would print "this program is
 * created by Bill Gates". After the patch, typing ".\victim.exe" prints
 * "this program is created by Ayzat Rizatdinov".
 * 
 * "victim.cpp" file itself does not change.
 */
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

  std::cout << "Enter the replacement string: ";
  std::string replacementString;
  std::getline(std::cin, replacementString);

  patch(file, targetString, replacementString);

  std::cout << "Replacement complete." << std::endl;

  file.close();

  return 0;
}