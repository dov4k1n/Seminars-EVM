#ifndef INCLUDE_CAR_LOADING_HPP
#define INCLUDE_CAR_LOADING_HPP

#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "car.hpp"

namespace dov4k1n {

std::vector<Car> load_cars_from(
  const std::string& input_path
) {
  std::ifstream input_file(input_path);
  auto cars_j = nlohmann::json::parse(input_file).at("cars");

  std::vector<Car> result;
  Car car;

  for (const nlohmann::json& car_j : cars_j) {
    car.set_id(car_j.at("id"));
    car.set_brand(car_j.at("brand"));
    car.set_model(car_j.at("model"));
    car.set_color(car_j.at("color"));
    car.set_fuel_capacity(car_j.at("fuel_capacity"));
    car.set_consumption_rate(car_j.at("consumption_rate"));

    result.push_back(car);
  }

  return result;
}

void save_cars_to(
  const std::string& output_path,
  const std::vector<Car>& cars
) {
  nlohmann::json cars_j;
  nlohmann::json car_j;

  for (const Car& car : cars) {
    car_j["id"] = car.get_id();
    car_j["brand"] = car.get_brand();
    car_j["model"] = car.get_model();
    car_j["color"] = car.get_color();
    car_j["fuel_capacity"] = car.get_fuel_capacity();
    car_j["consumption_rate"] = car.get_consumption_rate();

    cars_j["cars"].push_back(car_j);
  }

  std::ofstream output_file(output_path);
  output_file << std::setw(4) << cars_j << std::endl;
}

} // namespace dov4k1n

#endif // INCLUDE_CAR_LOADING_HPP