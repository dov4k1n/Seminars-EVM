/**
 * @file include/theater_algorithms_edit.hpp
 * @author Ayzat Rizatdinov (dov4k1n)
 *
 * Implementation of editing algorithm for the class Theater.
 */

#ifndef INCLUDE_THEATER_ALGORITHMS_EDIT_HPP_
#define INCLUDE_THEATER_ALGORITHMS_EDIT_HPP_

#include <vector>
#include <string>
#include <algorithm>
#include "theater.hpp"

namespace dov4k1n {

/**
 * @brief 
 */
void edit(
  std::vector<Theater>& theaters,
  const std::string& theater_name,
  const std::string& field_name,
  const std::string& replacement
) {
  auto theater = std::find_if(
    theaters.begin(), 
    theaters.end(),
    [&](const Theater& theater) { 
      return theater.get_name().contains(theater_name); 
    }
  );

  if (theater == std::end(theaters)) {
    throw std::invalid_argument("no such theater name");
  }

  else if (field_name == "name") {
    (*theater).set_name(replacement);
  }

  else if (field_name == "director") {
    (*theater).set_director(replacement);
  }

  else if (field_name == "address") {
    (*theater).set_address(replacement);
  }

  else if (field_name == "rating") {
    const double replacement_d = std::stod(replacement);
    (*theater).set_rating(replacement_d);
  }

  else {
    throw std::invalid_argument("no such field name");
  }

  (*theater).print_shifted();
}

} // namespace dov4k1n

#endif // INCLUDE_THEATER_ALGORITHMS_EDIT_HPP_