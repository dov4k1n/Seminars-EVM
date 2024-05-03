#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

bool is_literal_int(const std::string& str) {
  std::istringstream iss(str);
  int value;
  iss >> value;
  // Check if the entire string was consumed and no error occurred during conversion
  return !iss.fail() && iss.eof();
}

std::vector<std::string> split_root(const std::string& input) {
  std::vector<std::string> chunks;
  std::string chunk = "";

  for (int i = 1; i < input.size(); i++) {
    if (input[i] != '.' && input[i] != '[' && input[i] != ']') {
      chunk += input[i];
    } else if (chunk != "") {
      chunks.push_back(chunk);
      chunk = "";
    }
  }
  if (chunk != "") {
    chunks.push_back(chunk);
  }

  return chunks;
}

void jq(const json& inputedJson, const std::string& inputedRoot) {
  std::vector<std::string> chunked_root = split_root(inputedRoot);

  json temp;

  if (is_literal_int(chunked_root[0])) {
    temp = inputedJson[std::stoi(chunked_root[0])];
  } else {
    temp = inputedJson[chunked_root[0]];
  }

  for (int i = 1; i < chunked_root.size(); i++) {
    if (temp.is_object()) {
      temp = temp[chunked_root[i]];
    } else if (temp.is_array()) {
      temp = temp[std::stoi(chunked_root[i])];
    }
  }

  std::cout << temp.dump(2) << std::endl;
}

void jq(const json& inputedJson) {
  std::cout << inputedJson.dump(2) << std::endl;
}

int main(int argc, char *argv[]) {
  // "https://dummyjson.com/products";
  // "https://api.github.com/repos/jqlang/jq/commits?per_page=5";

  json inputedJson;
  std::cin >> inputedJson;

  if (std::cin.fail() && inputedJson.is_null()) {
    std:: cout << "Input JSON is null or input operation failed." << std::endl;
    return -1;
  }

  if (argc == 2) {
    jq(inputedJson, argv[1]);
  } else {
    jq(inputedJson);
  }

  return 0;
}