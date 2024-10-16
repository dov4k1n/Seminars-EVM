#include <iostream>
#include <vector>
#include <string>

#include "car.hpp"
#include "car_loading.hpp"
#include "io_helpers.hpp"
#include "car_algorithms_print.hpp"

using dov4k1n::Car;
using dov4k1n::load_cars_from;
using dov4k1n::save_cars_to;

int main(int argc, char* argv[]) {
  std::string file_name = "car";

  if (argc >= 2) {
    char tmp;

    if (std::sscanf(argv[1], "%s", &tmp) != 1) {
      std::cout << "error" << std::endl;
      return -1;
    }

    file_name = std::string(&tmp);
  }

  std::string input_path = "../data/";
  input_path.append(file_name);
  input_path.append(".json");

  std::vector<Car> cars = load_cars_from(input_path);

  while (true) {
    std::string user_type;
    std::vector<std::string> user_cmd;
    std::getline(std::cin, user_type);
    user_cmd = split(user_type, ' ');

    try {
      if (user_cmd.empty()) {
        throw std::invalid_argument("empty command");
      } 
      
      else if (user_cmd[0] == "--exit") {
        return 0;
      } 
      
      else if (user_cmd[0] == "--help") {
        print_help();
      }

      else if (user_cmd[0] == "--list") {
        print(cars);
      }  
      
      // else if (user_cmd[0] == "--edit") {
      //   if (user_cmd.size() != 1) {
      //     throw std::invalid_argument("wrong syntax");
      //   }

      //   std::cout << "Select theater to edit:" << std::endl;
      //   print_names(theaters);
      //   std::string theater_name;
      //   std::getline(std::cin, theater_name);

      //   std::cout << "Select field to edit:" << std::endl;
      //   Theater::print_field_names();
      //   std::string field_name;
      //   std::getline(std::cin, field_name);

      //   std::cout << "Enter replacement:" << std::endl;
      //   std::string replacement;
      //   std::getline(std::cin, replacement);
        
      //   edit(theaters, theater_name, field_name, replacement);
      // } 

      else if (user_cmd[0] == "--save") {
        if (user_cmd.size() < 2) {
          save_cars_to(input_path, cars);
        }
        
        else if (user_cmd.size() == 2) {
          std::string new_path = "../data/";
          new_path.append(user_cmd[1]);
          new_path.append(".json");

          save_cars_to(new_path, cars);
        }

        else {
          throw std::invalid_argument("unknown command");
        }
      } 
      
      else {
        throw std::invalid_argument("unknown command");
      }
    } 
    
    catch (const std::invalid_argument& e) {
      std::cerr << "Error: " << e.what() << "." << 
        " Type --help for commands." << 
      std::endl;
    }
  }

  return 0;
}