#ifndef INCLUDE_IO_HELPERS_HPP_
#define INCLUDE_IO_HELPERS_HPP_

#include <iostream>
#include <sstream>
#include <vector>

void print_help() {
  std::cout <<
    '\t' << "--list                             " << "to print cars" << std::endl <<
    
//    '\t' << "--edit                             " << "to edit car's info" << std::endl << std::endl <<

    '\t' << "--save                             " << "to save changes" << std::endl <<
    '\t' << "--save filename                    " << "to save changes into specific file" << std::endl <<
    '\t' << "--exit                             " << "to exit" << std::endl <<
    '\t' << "--help                             " << "to list available commands" << std::endl << std::endl;
}

std::vector<std::string> split(const std::string& s, const char& delim) {
  std::vector<std::string> result;
  std::stringstream ss(s);
  std::string item;

  while (getline(ss, item, delim)) {
    result.push_back(item);
  }

  return result;
}

#endif // INCLUDE_IO_HELPERS_HPP_