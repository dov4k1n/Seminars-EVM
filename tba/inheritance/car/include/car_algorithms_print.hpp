#ifndef INCLUDE_CAR_ALGORITHMS_PRINT_HPP_
#define INCLUDE_CAR_ALGORITHMS_PRINT_HPP_

#include <iostream>
#include <vector>
#include "car.hpp"

namespace dov4k1n {

std::ostream& operator<<(std::ostream& out, const Car& car) {
  out << '\t' << "id: " << car.id << std::endl;
  out << '\t' << "brand: " << car.brand << std::endl;
  out << '\t' << "model: " << car.model << std::endl;
  out << '\t' << "color: " << car.color << std::endl;
  out << '\t' << "fuel capacity: " << car.fuel_capacity << std::endl;
  out << '\t' << "consumption rate: " << car.consumption_rate << std::endl << std::endl;
  return out;
}

void print(const std::vector<Car>& cars) {
  for (const Car& car : cars) {
    car.print_shifted();
    // std::cout << car << std::endl;
    // std::cout << std::endl;
  }
}

/**
 * @brief Function prints names of Cars from std::vector.
 */
void print_names(const std::vector<Car>& cars) {
  for (const Car& car : cars) {
    std::cout << '\t' << car.get_id() << std::endl;
  }
  std::cout << std::endl;
}

} // namespace dov4k1n

#endif // INCLUDE_CAR_ALGORITHMS_PRINT_HPP_