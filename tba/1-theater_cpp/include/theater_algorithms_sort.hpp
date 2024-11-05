/**
 * @file include/theater_algorithms_sort.hpp
 * @author Ayzat Rizatdinov (dov4k1n)
 *
 * Implementation of sorting algorithms for the class Theater.
 */

#ifndef INCLUDE_THEATER_ALGORITHMS_SORT_HPP_
#define INCLUDE_THEATER_ALGORITHMS_SORT_HPP_

#include <algorithm> // for std::sort()
#include <vector>
#include "theater.hpp"

namespace dov4k1n {

/**
 * @brief Function sorts std::vector<Theater> by id.
 */
void sort_by_id(
  std::vector<Theater>& theaters,
  const bool& ascending = true
) {
  if (ascending) {
    std::sort(theaters.begin(), theaters.end(), 
      [](const Theater& a, const Theater& b) { 
        return a.get_id() < b.get_id();
      }
    );
  } else {
    std::sort(theaters.begin(), theaters.end(), 
      [](const Theater& a, const Theater& b) { 
        return a.get_id() >= b.get_id();
      }
    );
  }
}

/**
 * @brief Function sorts std::vector<Theater> by name.
 */
void sort_by_name(
  std::vector<Theater>& theaters,
  const bool& alphabetically = true
) {
  if (alphabetically) {
    std::sort(theaters.begin(), theaters.end(), 
      [](const Theater& a, const Theater& b) { 
        return a.get_name() < b.get_name();
      }
    );
  } else {
    std::sort(theaters.begin(), theaters.end(),
      [](const Theater& a, const Theater& b) { 
        return a.get_name() >= b.get_name();
      }
    );
  }
}

/**
 * @brief Function sorts std::vector<Theater> by director.
 */
void sort_by_director(
  std::vector<Theater>& theaters,
  const bool& alphabetically = true
) {
  if (alphabetically) {
    std::sort(theaters.begin(), theaters.end(), 
      [](const Theater& a, const Theater& b) { 
        return a.get_director() < b.get_director();
      }
    );
  } else {
    std::sort(theaters.begin(), theaters.end(), 
      [](const Theater& a, const Theater& b) { 
        return a.get_director() >= b.get_director();
      }
    );
  }
}

/**
 * @brief Function sorts std::vector<Theater> by rating.
 */
void sort_by_rating(
  std::vector<Theater>& theaters,
  const bool& ascending = true
) {
  if (ascending) {
    std::sort(theaters.begin(), theaters.end(), 
      [](const Theater& a, Theater& b) { 
        return a.get_rating() < b.get_rating();
      }
    );
  } else {
    std::sort(theaters.begin(), theaters.end(), 
      [](const Theater& a, Theater& b) { 
        return a.get_rating() >= b.get_rating();
      }
    );
  }
}

} // namespace dov4k1n

#endif // INCLUDE_THEATER_ALGORITHMS_SORT_HPP_