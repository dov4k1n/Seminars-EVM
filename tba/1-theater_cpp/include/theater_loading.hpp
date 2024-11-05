/**
 * @file include/theater_loading.hpp
 * @author Ayzat Rizatdinov (dov4k1n)
 *
 * Functions to load JSON data from file and to save it.
 */

#ifndef INCLUDE_THEATER_LOADING_HPP
#define INCLUDE_THEATER_LOADING_HPP

#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "theater.hpp"

namespace dov4k1n {

std::vector<Theater> load_theaters_from(
  const std::string& input_path
) {
  std::ifstream input_file(input_path);
  auto theaters_j = nlohmann::json::parse(input_file).at("theaters");

  std::vector<Theater> result;
  Theater theater;

  for (const nlohmann::json& theater_j : theaters_j) {
    theater.set_id(theater_j.at("id"));
    theater.set_name(theater_j.at("name"));
    theater.set_director(theater_j.at("director"));
    theater.set_address(theater_j.at("address"));
    theater.set_rating(theater_j.at("rating"));

    result.push_back(theater);
  }

  return result;
}

void save_theaters_to(
  const std::string& output_path,
  const std::vector<Theater>& theaters
) {
  nlohmann::json theaters_j;
  nlohmann::json theater_j;

  for (const Theater& theater : theaters) {
    theater_j["id"] = theater.get_id();
    theater_j["name"] = theater.get_name();
    theater_j["director"] = theater.get_director();
    theater_j["address"] = theater.get_address();
    theater_j["rating"] = theater.get_rating();

    theaters_j["theaters"].push_back(theater_j);
  }

  std::ofstream output_file(output_path);
  output_file << std::setw(4) << theaters_j << std::endl;
}

} // namespace dov4k1n

#endif // INCLUDE_THEATER_LOADING_HPP