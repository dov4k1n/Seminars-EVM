#include <string>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <algorithm>

std::string uint64ToString(uint64_t value) {
  std::ostringstream oss;
  oss << value;
  
  std::string asciiText = oss.str();
  
  return asciiText;
}

uint64_t hexStringToUInt64(std::string hexString) {
  uint64_t result = 0;

  for (char c : hexString) {
    result <<= 4;

    if (c >= '0' && c <= '9') {
      result += c - '0';
    } else if (c >= 'A' && c <= 'F') {
      result += c - 'A' + 10;
    } else if (c >= 'a' && c <= 'f') {
      result += c - 'a' + 10;
    } else {
      throw std::invalid_argument("Invalid hex string: " + hexString);
    }
  }

  return result;
}

std::string uint64_to_string(const uint64_t& value) {
  std::string result;
  result.clear();
  result.reserve(20); // max. 20 digits possible
  uint64_t q = value;
  do {
    result += "0123456789"[ q % 10 ];
    q /= 10;
  } while ( q );
  std::reverse( result.begin(), result.end() );
  return result;
}

std::string string_to_hexString(const std::string& input) {
  static const char hex_digits[] = "0123456789ABCDEF";

  std::string output;
  output.reserve(input.length() * 2);
  for (unsigned char c : input) {
    output.push_back(hex_digits[c >> 4]);
    output.push_back(hex_digits[c & 15]);
  }
  //std::cout << output << std::endl;
  return output;
}

void patch(const std::string& user_text) {
  uint64_t user_value = std::stoull(string_to_hexString(user_text), nullptr, 0);
  std::cout << "inside patch user_value is: " << user_value << std::endl;

  uint64_t x;   
  std::stringstream ss;
  ss << string_to_hexString(user_text);
  ss >> x;
  std::cout << "patch: " << x << std::endl;
}

int main() {
  std::cout << "what should i search for and change?" << std::endl;
	std::string user_text;
	std::getline(std::cin, user_text);

  std::cout << "string_to_hexString: " << string_to_hexString(user_text) << std::endl;

  std::cout << "hexStringToUInt64: " << hexStringToUInt64(string_to_hexString(user_text)) << std::endl;

  patch(user_text);

  std::cout << "hexStringToUInt64 to string: " << uint64ToString(hexStringToUInt64(string_to_hexString(user_text))) << std::endl;



  // std::cout << hex_to_ascii(747865742e) << std::endl;
  // std::cout << hex_to_ascii(e274657874) << std::endl;
  //std::cout << hex_to_ascii(500236121134) << std::endl;
  

  return 0;
}