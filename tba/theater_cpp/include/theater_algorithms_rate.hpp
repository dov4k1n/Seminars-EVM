/**
 * @file include/theater_algorithms_rate.hpp
 * @author Ayzat Rizatdinov (dov4k1n)
 *
 * Implementation of rating algorithms for the class Theater.
 */

#ifndef INCLUDE_THEATER_ALGORITHMS_RATE_HPP_
#define INCLUDE_THEATER_ALGORITHMS_RATE_HPP_

#include <vector>
#include <string>
#include "theater.hpp"

namespace dov4k1n {

/**
 * @brief Function returns element with higher rating.
 */
Theater get_most_rated(
  const std::vector<Theater>& theaters
) {
  Theater max;

  for (const Theater& theater : theaters)
    if (max.get_rating() < theater.get_rating()) 
      max = theater;
  
  return max;
}

/**
 * @brief Function returns vector of Theaters with rating higher than number X.
 */
std::vector<Theater> greater_than(
  const std::vector<Theater>& theaters,
  const double& X
) {
  std::vector<Theater> result;

  for (const Theater& theater : theaters)
    if (theater.get_rating() > X) 
      result.push_back(theater);

  return result;
}

/**
 * @brief Function returns vector of Theaters with rating higher than
 * the given theater's.
 */
std::vector<Theater> greater_than(
  const std::vector<Theater>& theaters,
  const std::string& theater_name
) {
  auto given_theater = std::find_if(
    theaters.begin(), 
    theaters.end(),
    [&](const Theater& theater) { 
      return theater.get_name().contains(theater_name); 
    }
  );

  if (given_theater == std::end(theaters)) {
    throw std::invalid_argument("no such theater_name");
  }

  std::vector<Theater> result;

  for (const Theater& theater : theaters)
    if (theater.get_rating() > (*given_theater).get_rating())
      result.push_back(theater);

  return result;
}

} // namespace dov4k1n

#endif // INCLUDE_THEATER_ALGORITHMS_RATE_HPP_