#ifndef INCLUDE_TRUCK_HPP_
#define INCLUDE_TRUCK_HPP_

#include <iostream>
#include "vehicle.hpp"

class Truck : public Vehicle {
 private:
  double carry_capacity;

 public:
  Truck(
    unsigned id = unsigned(),
    std::string brand = std::string(),
    std::string model = std::string(),
    std::string color = std::string(),
    double fuel_capacity = double(),
    double consumption_rate = double(),
    double carry_capacity = double()
  ) :
    Vehicle(
      id,
      brand,
      model,
      color,
      fuel_capacity,
      consumption_rate
    ),
    carry_capacity(carry_capacity)
  {
    std::cout << 
      "Truck #"<< (*this).get_id() << " " << (*this).get_brand() << " constructed." << std::endl <<
    std::endl;
  }

  ~Truck() {
    std::cout << 
      "~ Truck #"<< (*this).get_id() << " " << (*this).get_brand() << " destructed." << std::endl <<
    std::endl;
  }

  double get_carry_capacity() const { return carry_capacity; }
  void set_carry_capacity(const double& new_cap) { carry_capacity = new_cap; }

  void print_transportation_cost() const {
    double fuel_price = 40;
    double transportation_cost;

    if (carry_capacity > 0) {
      transportation_cost = (*this).get_consumption_rate() / 100.0 * fuel_price / carry_capacity; 
    } else {
      transportation_cost = -1;
    }
    
    std::cout << '\t' << "transportation_cost: " << transportation_cost << std::endl << std::endl;
  }
};

#endif // INCLUDE_TRUCK_HPP_