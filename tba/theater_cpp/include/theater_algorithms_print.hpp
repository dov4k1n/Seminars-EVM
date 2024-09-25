/**
 * @file include/theater_algorithms_print.hpp
 * @author Ayzat Rizatdinov (dov4k1n)
 *
 * Implementation of printing algorithms for the class Theater.
 */

#ifndef INCLUDE_THEATER_ALGORITHMS_PRINT_HPP_
#define INCLUDE_THEATER_ALGORITHMS_PRINT_HPP_

#include <iostream>
#include <vector>
#include "theater.hpp"

namespace dov4k1n {

/**
 * @brief Function prints information of Theaters from std::vector.
 */
void print(const std::vector<Theater>& theaters) {
  for (const Theater& theater : theaters) {
    theater.print_shifted();
    std::cout << std::endl;
  }
}

/**
 * @brief Function prints names of Theaters from std::vector.
 */
void print_names(const std::vector<Theater>& theaters) {
  for (const Theater& theater : theaters) {
    std::cout << '\t' << theater.get_name() << std::endl;
  }
  std::cout << std::endl;
}

} // namespace dov4k1n

#endif // INCLUDE_THEATER_ALGORITHMS_PRINT_HPP_