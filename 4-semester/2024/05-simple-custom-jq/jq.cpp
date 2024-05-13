#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

std::vector<std::string> split_root(const std::string& input) {
  std::vector<std::string> chunks;
  std::string chunk = "";

  for (int i = 0; i < input.size(); i++) {
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
  int root_size = chunked_root.size();

  json result = inputedJson;
  bool root_has_star = false;
  int star_index;

  for (int i = 0; i < root_size; i++) {
    if (result.is_object()) {

      result = result[chunked_root[i]];

    } else if (result.is_array()) {

      if (chunked_root[i] == "*") {
        root_has_star = true;
        star_index = i;
        break;
      }

      result = result[std::stoi(chunked_root[i])];
    }
  }

  if (root_has_star) {
    json result_chunk;

    for (int i = 0; i < result.size(); i++) {
      result_chunk = result[i];

      for (int j = star_index + 1; j < root_size; j++) {
        result_chunk = result_chunk[chunked_root[j]];
      }
      
      std::cout << chunked_root[root_size - 1] << " " << i << ": " << result_chunk.dump(2) << std::endl;
    }
  } else {
    std::cout << result.dump(2) << std::endl;
  }
}

void jq(const json& inputedJson) {
  std::cout << inputedJson.dump(2) << std::endl;
}

int main(int argc, char *argv[]) {
  // https://dummyjson.com/products
  // https://api.github.com/repos/jqlang/jq/commits?per_page=5

  json inputedJson;
  std::cin >> inputedJson;

  if (std::cin.fail() || inputedJson.is_null()) {
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