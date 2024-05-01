#include <iostream>
#include <vector>
#include <sstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

std::vector<std::string> split_root(const std::string& input) {
  std::vector<std::string> chunks;
  std::istringstream iss(input);
  std::string chunk;
  iss.ignore(1);

  while (std::getline(iss, chunk, '.')) {
    if (!chunk.empty()) {
      chunks.push_back(chunk);
    }
  }
  chunks.pop_back();

  return chunks;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
		std::cout << "Need an exe file!" << std::endl;
		std::cout << argv[0] << " <file name>" << std::endl;
		return -1;
	}

  if (argc == 2) {
    std::vector<std::string> chunked_root = split_root(argv[1]);

    
  }

  try {
    const std::string productsUrl = "https://dummyjson.com/products";
    const std::string commitsUrl = "https://api.github.com/repos/jqlang/jq/commits?per_page=5";

    json inputedJson;
    std::cin >> inputedJson;
    std::cout << inputedJson.dump(2);

    

  } catch (const std::exception& e) {
    std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}