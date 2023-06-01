#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>

std::vector<uint8_t> encode(const std::string& text) {
  std::vector<uint8_t> encoded;
  for (char c : text) {
    encoded.push_back(static_cast<uint8_t>(c));
  }
  return encoded;
}

std::string decode(const std::vector<uint8_t>& encoded) {
  std::string decoded;
  for (uint8_t c : encoded) {
    decoded += static_cast<char>(c);
  }
  return decoded;
}

/*
std::vector<uint64_t> encode(std::string line) {
  const int BLOCK_SIZE = 8;
  std::vector<uint64_t> result;
  
  // Pad the line with zeros if its size is not a multiple of BLOCK_SIZE
  int num_padding = BLOCK_SIZE - line.size() % BLOCK_SIZE;
  if (num_padding < BLOCK_SIZE) {
    line.insert(line.size(), num_padding, '\0');
  }
  
  // Encode each BLOCK_SIZE-byte block of the line into a uint64_t variable
  for (int i = 0; i < line.size(); i += BLOCK_SIZE) {
    uint64_t block = 0;
    for (int j = 0; j < BLOCK_SIZE; j++) {
      block |= static_cast<uint64_t>(line[i + j]) << (8 * (BLOCK_SIZE - j - 1));
    }
    result.push_back(block);
  }
  
  return result;
}

std::string decode(std::vector<uint64_t> blocks) {
  std::string result;
  
  // Decode each uint64_t block into 8 bytes and concatenate them into a string
  for (auto block : blocks) {
    for (int j = 0; j < 8; j++) {
        result += static_cast<char>((block >> (8 * (7 - j))) & 0xFF);
    }
  }
  
  return result;
}

*/

/*
uint64_t encode(const std::string& str) {
  uint64_t result = 0;
  size_t len = str.length();

  for (size_t i = 0; i < len; i++) {
    result = (result << 8) | uint64_t(str[i]);
  }
  return result;
}


std::string decode(uint64_t num) {
  std::string result = "";

  // Decode each 8-bit character by shifting right and masking with 0xFF
  for (int i = 7; i >= 0; i--) {
    uint64_t ch = (num >> (i * 8)) & 0xFF;
    if (ch != 0) {
      result += ch;
    }
  }
  return result;
}
*/

int main() {
  std::string str = "Ayzat Rizatdinov";
  std::vector<uint8_t> encoded = encode(str);
  //std::cout << "Encoded value: " << encoded << std::endl;

  // Print out the encoded uint64_t variables in binary format
  for (auto block : encoded) {
    std::bitset<8> bits(block);
    std::cout << bits << " ";
  }
  std::cout << std::endl;

  for (uint8_t block : encoded) {
    std::cout << block << " ";
  }
  std::cout << std::endl;

  std::string decoded = decode(encoded);
  std::cout << "Decoded value: " << decoded << std::endl;
  return 0;
}