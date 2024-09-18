/**
 * @file include/theater.hpp
 * @author Ayzat Rizatdinov (dov4k1n)
 *
 * Class Theater implementation.
 */

#ifndef INCLUDE_THEATER_HPP_
#define INCLUDE_THEATER_HPP_

#include <iostream>
#include <vector>
#include <algorithm>

namespace dov4k1n {

/**
 * @brief Class for holding the data of the theater.
 */
class Theater {
 private:
  std::string name;
  std::string director;
  std::string address;
  double rating;

 public:
  /**
   * @brief Initialization list of class Theater.
   */
  Theater(
    std::string name = std::string(), 
    std::string director = std::string(), 
    std::string address = std::string(),
    double rating = 0.0
  ) : 
    name(name), 
    director(director), 
    address(address), 
    rating(rating) 
  {}
  
  /**
   * @brief Copy constructor.
   */
  Theater(const Theater& copy) : 
    name(copy.name), 
    director(copy.director),
    address(copy.address),
    rating(copy.rating) 
  {}

  /**
   * @brief Assignment operator overload.
   */
  Theater& operator=(const Theater& other) {
    if (this != &other) {
      name = other.name;
      director = other.director;
      address = other.address;
      rating = other.rating;
    }
    return *this;
  }

  /**
   * @brief Method returns theater's name.
   */
  std::string get_name() const { return name; }

  /**
   * @brief Method returns theater's director.
   */
  std::string get_director() const { return director; }

  /**
   * @brief Method returns theater's address.
   */
  std::string get_address() const { return address; }

  /**
   * @brief Method returns theater's rating.
   */
  double get_rating() const { return rating; }

  /**
   * @brief Method replaces theater's name.
   */
  void set_name(std::string& new_name) { name = new_name; }

  /**
   * @brief Method replaces theater's director.
   */
  void set_director(std::string& new_director) { director = new_director; }

  /**
   * @brief Method replaces theater's address.
   */
  void set_address(std::string& new_address) { address = new_address; }

  /**
   * @brief Method replaces theater's rating.
   */
  void set_rating(double& new_rating) { rating = new_rating; }

  /**
   * @brief Method prints theater's data.
   */
  void print() const {
    std::cout << "name: " << this->get_name() << std::endl;
    std::cout << "director: " << this->get_director() << std::endl;
    std::cout << "address: " << this->get_address() << std::endl;
    std::cout << "rating: " << this->get_rating() << std::endl;
  }

  /**
   * @brief Method prints theater's data shifted by \t.
   */
  void print_shifted() const {
    std::cout << '\t' << "name: " << this->get_name() << std::endl;
    std::cout << '\t' << "director: " << this->get_director() << std::endl;
    std::cout << '\t' << "address: " << this->get_address() << std::endl;
    std::cout << '\t' << "rating: " << this->get_rating() << std::endl;
  }
};

} // namespace dov4k1n

#endif // INCLUDE_THEATER_HPP_