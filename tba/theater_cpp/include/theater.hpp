/**
 * @file include/theater.hpp
 * @author Ayzat Rizatdinov (dov4k1n)
 *
 * Class Theater implementation.
 */

#ifndef INCLUDE_THEATER_HPP_
#define INCLUDE_THEATER_HPP_

#include <iostream>

namespace dov4k1n {

/**
 * @brief Class for holding the data of the theater.
 */
class Theater {
 private:
  static inline unsigned count{};
  unsigned id;
  std::string name;
  std::string director;
  std::string address;
  double rating;

 public:
  /**
   * @brief Initialization list of class Theater.
   */
  Theater(
    unsigned id = unsigned(),
    std::string name = std::string(), 
    std::string director = std::string(), 
    std::string address = std::string(),
    double rating = double()
  ) : 
    id(id),
    name(name), 
    director(director), 
    address(address), 
    rating(rating) 
  {
    ++count;
    // id = count;
  }
  
  /**
   * @brief Copy constructor.
   */
  Theater(const Theater& copy) : 
    id(copy.id),
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
      id = other.id,
      name = other.name;
      director = other.director;
      address = other.address;
      rating = other.rating;
    }
    return *this;
  }

  /**
   * @brief Method returns theater's id.
   */
  unsigned get_id() const { return id; }

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
   * @brief Method replaces theater's id.
   */
  void set_id(const int& new_id) { id = new_id; }
  void set_id(int& new_id) { id = new_id; }

  /**
   * @brief Method replaces theater's name.
   */
  void set_name(const std::string& new_name) { name = new_name; }
  void set_name(std::string& new_name) { name = new_name; }

  /**
   * @brief Method replaces theater's director.
   */
  void set_director(const std::string& new_director) { director = new_director; }
  void set_director(std::string& new_director) { director = new_director; }

  /**
   * @brief Method replaces theater's address.
   */
  void set_address(const std::string& new_address) { address = new_address; }
  void set_address(std::string& new_address) { address = new_address; }

  /**
   * @brief Method replaces theater's rating.
   */
  void set_rating(const double& new_rating) { rating = new_rating; }
  void set_rating(double& new_rating) { rating = new_rating; }

  /**
   * @brief Method prints theater's data.
   */
  void print() const {
    std::cout << "id: " << this->get_id() << std::endl;
    std::cout << "name: " << this->get_name() << std::endl;
    std::cout << "director: " << this->get_director() << std::endl;
    std::cout << "address: " << this->get_address() << std::endl;
    std::cout << "rating: " << this->get_rating() << std::endl;
  }

  /**
   * @brief Method prints theater's data shifted by \t.
   */
  void print_shifted() const {
    std::cout << '\t' << "id: " << this->get_id() << std::endl;
    std::cout << '\t' << "name: " << this->get_name() << std::endl;
    std::cout << '\t' << "director: " << this->get_director() << std::endl;
    std::cout << '\t' << "address: " << this->get_address() << std::endl;
    std::cout << '\t' << "rating: " << this->get_rating() << std::endl;
  }

  /**
   * @brief Method prints class's editable field names.
   */
  static void print_field_names() {
    std::cout << '\t' << "id" << std::endl;
    std::cout << '\t' << "name" << std::endl;
    std::cout << '\t' << "director" << std::endl;
    std::cout << '\t' << "address" << std::endl;
    std::cout << '\t' << "rating" << std::endl;
  }
};

} // namespace dov4k1n

#endif // INCLUDE_THEATER_HPP_