/**
 * @file src/main/main.cpp
 * @author Ayzat Rizatdinov (dov4k1n)
 *
 * Main function of theaters database console application.
 */

#include <iostream>
#include <vector>
#include <string>

#include "theater.hpp"
#include "theater_loading.hpp"
#include "theater_algorithms_edit.hpp"
#include "theater_algorithms_print.hpp"
#include "theater_algorithms_rate.hpp"
#include "theater_algorithms_sort.hpp"
#include "io_helpers.hpp"

using dov4k1n::Theater;
using dov4k1n::load_theaters_from;
using dov4k1n::save_theaters_to;

int main(int argc, char* argv[]) {
  std::string file_name = "theater";

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

  std::vector<Theater> theaters = load_theaters_from(input_path);

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
        print(theaters);
      } 
      
      else if (user_cmd[0] == "--greater-than") {
        if (user_cmd.size() < 2) {
          throw std::invalid_argument("wrong syntax");
        }

        else {
          double x = std::stod(user_cmd[1]);
          print(greater_than(theaters, x));
        }
      } 
      
      else if (user_cmd[0] == "--most-rated") {
        get_most_rated(theaters).print_shifted();
        std::cout << std::endl;
      } 
      
      else if (user_cmd[0] == "--edit") {
        if (user_cmd.size() != 1) {
          throw std::invalid_argument("wrong syntax");
        }

        std::cout << "Select theater to edit:" << std::endl;
        print_names(theaters);
        std::string theater_name;
        std::getline(std::cin, theater_name);

        std::cout << "Select field to edit:" << std::endl;
        Theater::print_field_names();
        std::string field_name;
        std::getline(std::cin, field_name);

        std::cout << "Enter replacement:" << std::endl;
        std::string replacement;
        std::getline(std::cin, replacement);
        
        edit(theaters, theater_name, field_name, replacement);
      } 
      
      else if (user_cmd[0] == "--sort-by-id") {
        if (user_cmd.size() < 2) {
          sort_by_id(theaters);
        }
        
        else if (user_cmd[1] != "-desc" || user_cmd.size() > 2) {
          throw std::invalid_argument("unknown command");
        }

        else sort_by_id(theaters, false);
      } 
      
      else if (user_cmd[0] == "--sort-by-rating") {
        if (user_cmd.size() < 2) {
          sort_by_rating(theaters);
        }
        
        else if (user_cmd[1] != "-desc" || user_cmd.size() > 2) {
          throw std::invalid_argument("unknown command");
        }

        else sort_by_rating(theaters, false);
      } 
      
      else if (user_cmd[0] == "--sort-by-name") {
        if (user_cmd.size() < 2) {
          sort_by_name(theaters);
        }
        
        else if (user_cmd[1] != "-desc" || user_cmd.size() > 2) {
          throw std::invalid_argument("unknown command");
        }

        else sort_by_name(theaters, false);
      } 
      
      else if (user_cmd[0] == "--sort-by-director") {
        if (user_cmd.size() < 2) {
          sort_by_director(theaters);
        }
        
        else if (user_cmd[1] != "-desc" || user_cmd.size() > 2) {
          throw std::invalid_argument("unknown command");
        }

        else sort_by_director(theaters, false);
      }

      else if (user_cmd[0] == "--save") {
        if (user_cmd.size() < 2) {
          save_theaters_to(input_path, theaters);
        }
        
        else if (user_cmd.size() == 2) {
          std::string new_path = "../data/";
          new_path.append(user_cmd[1]);
          new_path.append(".json");

          save_theaters_to(new_path, theaters);
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