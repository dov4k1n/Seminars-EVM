/**
 * @file include/io_helpers.hpp
 * @author Ayzat Rizatdinov (dov4k1n)
 *
 * Functions for IO handling.
 */

#ifndef INCLUDE_IO_HELPERS_HPP_
#define INCLUDE_IO_HELPERS_HPP_

#include <iostream>
#include <sstream>
#include <vector>

void print_help() {
  std::cout <<
    '\t' << "--friend                           " << "to showcase friend example" << std::endl <<

    '\t' << "--list                             " << "to print theaters" << std::endl <<
    '\t' << "--greater-than X                   " << "to print theaters with rating greater than number X" << std::endl <<
    '\t' << "--greater-than theater_name        " << "to print theaters with rating greater than number X" << std::endl <<
    '\t' << "--most-rated                       " << "to print most rated theater"<< std::endl << std::endl <<
    
    '\t' << "--edit                             " << "to edit theater's info" << std::endl << std::endl <<

    '\t' << "sorting ascending by default. to change add flag -desc" << std::endl << std::endl <<

    '\t' << "--sort-by-id                       " << "to sort theaters by id" << std::endl <<
    '\t' << "--sort-by-rating                   " << "to sort theaters by rating" << std::endl <<
    '\t' << "--sort-by-name                     " << "to sort theaters by name" << std::endl <<
    '\t' << "--sort-by-director                 " << "to sort theaters by director" << std::endl << std::endl <<

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