/**
 * @file include/theater_algorithms.hpp
 * @author Ayzat Rizatdinov (dov4k1n)
 *
 * Implementation of algorithms for the class Theater.
 */

#ifndef INCLUDE_THEATER_ALGORITHMS_HPP_
#define INCLUDE_THEATER_ALGORITHMS_HPP_

#include <algorithm>
#include <vector>
#include "theater.hpp"

namespace dov4k1n {

/**
 * @brief Method prints theater's data shifted by \t.
 */
Theater get_most_rated(const Theater& A, const Theater& B) {
  if (A.get_rating() > B.get_rating())
    return A;
  else
    return B;
}

Theater get_most_rated(const std::vector<Theater>& theater_vect) {
  Theater max;

  for (const Theater& theater : theater_vect) {
    max = get_most_rated(theater, max);
  }

  return max;
}

bool cmp(const Theater& a, const Theater& b) { 
  return a.get_name() >= b.get_name(); 
}

void sort_by_name(
  std::vector<Theater>& theater_vect,
  const bool& alphabetically = true
) {
  std::sort(theater_vect.begin(), theater_vect.end(), cmp);
}

} // namespace dov4k1n

#endif // INCLUDE_THEATER_ALGORITHMS_HPP_