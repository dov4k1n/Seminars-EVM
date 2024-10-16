#ifndef INCLUDE_CAR_HPP_
#define INCLUDE_CAR_HPP_

#include <iostream>

namespace dov4k1n {

class Car {
 private:
  static inline unsigned count_constructed{};
  static inline unsigned count_destructed{};
  unsigned id;
  std::string brand;
  std::string model;
  std::string color;
  double fuel_capacity; // in liters
  double consumption_rate; // liters / 100 km

 public:
  Car(
    unsigned id = unsigned(),
    std::string brand = std::string(),
    std::string model = std::string(),
    std::string color = std::string(),
    double fuel_capacity = double(),
    double consumption_rate = double()
  ) :
    id(id),
    brand(brand),
    model(model),
    color(color),
    fuel_capacity(fuel_capacity),
    consumption_rate(consumption_rate)
  {
    ++count_constructed;
    // id = count_constructed;
    
    std::cout << 
      "Car #"<< id << " constructed. Total constructed cars count is " <<
      count_constructed << std::endl <<
    std::endl;
  }

  Car(const Car& copy) :
    id(copy.id),
    brand(copy.brand),
    model(copy.model),
    color(copy.color),
    fuel_capacity(copy.fuel_capacity),
    consumption_rate(copy.consumption_rate)
  {}

  Car& operator=(const Car& other) {
    if (this != &other) {
      id = other.id;
      brand = other.brand;
      model = other.model;
      color = other.color;
      fuel_capacity = other.fuel_capacity;
      consumption_rate = other.consumption_rate;
    }

    return *this;
  }

  ~Car() {
    ++count_destructed;

    std::cout << 
      "Car #"<< id << " is destructed. Total cars left count is " << 
      count_constructed - count_destructed << std::endl <<
    std::endl;
  }

  unsigned get_id() const { return id; }
  std::string get_brand() const { return brand; }
  std::string get_model() const { return model; }
  std::string get_color() const { return color; }
  double get_fuel_capacity() const { return fuel_capacity; }
  double get_consumption_rate() const { return consumption_rate; }

  void set_id(const unsigned& new_id) { id = new_id; }
  void set_brand(const std::string& new_brand) { brand = new_brand; }
  void set_model(const std::string& new_model) { model = new_model; }
  void set_color(const std::string& new_color) { color = new_color; }
  void set_fuel_capacity(const double& new_fuel_capacity) { fuel_capacity = new_fuel_capacity; }
  void set_consumption_rate(const double& new_consumption_rate) { consumption_rate = new_consumption_rate; }

  void print_shifted() const {
    std::cout << '\t' << "id: " << this->get_id() << std::endl;
    std::cout << '\t' << "brand: " << this->get_brand() << std::endl;
    std::cout << '\t' << "model: " << this->get_model() << std::endl;
    std::cout << '\t' << "color: " << this->get_color() << std::endl;
    std::cout << '\t' << "fuel capacity: " << this->get_fuel_capacity() << std::endl;
    std::cout << '\t' << "consumption rate: " << this->get_consumption_rate() << std::endl << std::endl;
  }

  void print_capable_driving_range() {
    std::cout << "Capable driving range is " << fuel_capacity / consumption_rate << std::endl << std::endl;
  }

  friend std::ostream& operator<<(std::ostream& out, const Car& car);
}; // class Car

}

#endif // INCLUDE_CAR_HPP_