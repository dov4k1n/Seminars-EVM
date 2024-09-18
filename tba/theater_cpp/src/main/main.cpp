#include "theater.hpp"
#include "theater_algorithms.hpp"
#include "theater_list.hpp"

using std::cout;
using std::cin;
using std::endl;

using dov4k1n::Theater;
// using dov4k1n::get_most_rated;
// using dov4k1n::sort_by_name;
using dov4k1n::theater_vect;

int main() {
  while (true) {
    cout << 
      "Use commands: " <<
      "--most-rated, " <<
      "--sort-by-name, " <<
      "--search, " <<
      "--exit" <<
      endl << endl;
    
    std::string user_cmd;
    cin >> user_cmd;


    if (user_cmd == "--exit") {

      return 0;

    } else if (user_cmd == "--most-rated") {

      Theater most_rated = get_most_rated(theater_vect);

      cout << endl << "Most rated theater:" << endl << endl;
      most_rated.print();
      cout << endl;

    } else if (user_cmd == "--sort-by-name") {

      sort_by_name(theater_vect, false);

      cout << "Sorted by name in reverse alphabetical order:" << endl << endl;
      for (const Theater& theater : theater_vect) {
        theater.print();
        cout << endl;
      }

    } else {
      
      return 0;
      
    }
  }

  return 0;
}