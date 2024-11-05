#ifndef INCLUDE_VEHICLE_HPP_ 
#define INCLUDE_VEHICLE_HPP_

#include <iostream>

class Vehicle {
 private:
  unsigned id;
  std::string brand;
  std::string model;
  std::string color;
  double fuel_capacity; // in liters
  double consumption_rate; // liters / 100 km

 public:
  Vehicle(
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
    std::cout << 
      "Vehicle #"<< id << " " << brand <<  " constructed." << std::endl <<
    std::endl;
  }

  Vehicle(const Vehicle& copy) :
    id(copy.id),
    brand(copy.brand),
    model(copy.model),
    color(copy.color),
    fuel_capacity(copy.fuel_capacity),
    consumption_rate(copy.consumption_rate)
  {
    brand += " copied";
    std::cout << "copying..." << std::endl;
  }

  Vehicle& operator=(const Vehicle& other) {
    if (this != &other) {
      id = other.id;
      brand = other.brand;
      model = other.model;
      color = other.color;
      fuel_capacity = other.fuel_capacity;
      consumption_rate = other.consumption_rate;

      brand += " assigned";
      std::cout << "assigning..." << std::endl;
    }

    return *this;
  }

  ~Vehicle() {
    std::cout << 
      "~ Vehicle #"<< id << " " << brand << " destructed." << std::endl <<
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

  void print_driving_range() const {
    double driving_range;
    
    if (consumption_rate > 0) 
      driving_range = fuel_capacity / consumption_rate * 100.0;
    else {
      driving_range = 0.0;
    };

    std::cout << '\t' << "driving range: " << driving_range << std::endl << std::endl;
  }

  friend std::ostream& operator<<(std::ostream& out, const Vehicle& Vehicle);
};

#endif // INCLUDE_VEHICLE_HPP_