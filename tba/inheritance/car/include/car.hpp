#ifndef INCLUDE_CAR_HPP_
#define INCLUDE_CAR_HPP_

#include <iostream>
#include "vehicle.hpp"

class Car : public Vehicle {
 public:
  Car(
    unsigned id = unsigned(),
    std::string brand = std::string(),
    std::string model = std::string(),
    std::string color = std::string(),
    double fuel_capacity = double(),
    double consumption_rate = double()
  ) :
    Vehicle(
      id,
      brand,
      model,
      color,
      fuel_capacity,
      consumption_rate
    )
  {
    std::cout << 
      "Car #"<< (*this).get_id() << " " << (*this).get_brand() << " constructed." << std::endl <<
    std::endl;
  }

  ~Car() {
    std::cout << 
      "~ Car #"<< (*this).get_id() << " " << (*this).get_brand() << " destructed." << std::endl <<
    std::endl;
  }
};

#endif // INCLUDE_CAR_HPP_