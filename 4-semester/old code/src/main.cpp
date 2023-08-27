#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdint>
#include <ctime>

#include "funs.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "Need an exe file!" << std::endl;
		std::cout << argv[0] << " <file name>" << std::endl;
		return -1;
	}

	FILE *f = fopen(argv[1], "rb");
	if (f == NULL) {
		std::cout << "Error openning file" << std::endl;
		return -1;
	}

	exe_info exe;
  
	int ret;
	if ( (ret = read_exe_info(&exe, f)) < 0 ) {
		std::cout << "error reading exe file: " << ret << std::endl;
		fclose(f);
		return -1;
	}

  fclose(f);
  
	print_exe_info(&exe);

  std::cout << "what should i search for and change?" << std::endl;
	std::string user_searching_text = "";
	std::getline(std::cin, user_searching_text);

  std::cout << "change to what?" << std::endl;
	std::string user_changeto_text = "";
	std::getline(std::cin, user_changeto_text);

  FILE *f = fopen(argv[1], "wb");
	if (f == NULL) {
		std::cout << "Error openning file" << std::endl;
		return -1;
	}

  //patch(f, &exe, user_searching_text, user_changeto_text);

	fclose(f);

	return 0;
}