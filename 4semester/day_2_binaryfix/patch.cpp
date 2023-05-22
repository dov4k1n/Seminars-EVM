#include <iostream>
#include <string>

int patch(FILE *f, std::string user_text) {
	fseek(f, 9224, SEEK_SET);
	// можно так переместиться сразу? или нужно поиск строки внутри файла сделать?
	int ret;
	int ret = fwrite(user_text, sizeof(user_text), 1, f);
	// нужно текст из ASCII в HEX перевести? или использовать массив char'ов и заменять каждый байт?
	// если через массив char'ов, можно пользователю написать ограничение на количество символов? 
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "Need an exe file!" << std::endl;
		std::cout << argv[0] << " <file name>" << std::endl;
		return -1;
	}

	FILE *f = fopen( argv[1], "wb");
	if (f == NULL) {
		std::cout << "Error openning file" << std::endl;
		return -1;
	}

	std::cout << "what should i search for and change?" << std::endl;
	std::string user_text;
	std::getline(std::cin, user_text);

  return 0;
}