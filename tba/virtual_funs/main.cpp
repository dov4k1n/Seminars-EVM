#include <iostream>
#include <vector>

class Profession {
 private:
  std::string name;
  double salary;

 public:
  Profession(
    std::string name = std::string(),
    double salary = double()
  ) : 
    name(name), 
    salary(salary) 
  {}

  std::string get_name() const { return name; }
  double get_salary() const { return salary; }
  
  virtual void print_salary() const = 0;
};

class Courier: public Profession {
 public:
  Courier(
    std::string name = std::string(),
    double salary = double()
  ) :
    Profession(name, salary)
  {}

  void print_salary() const override { 
    std::cout << 
      "Courier " << get_name() << 
      "'s salary is " << get_salary() << std::endl 
    << std::endl; 
  }
};

class SoftwareEngineer: public Profession {
 public:
  SoftwareEngineer(
    std::string name = std::string(),
    double salary = double()
  ) :
    Profession(name, salary)
  {}

  void print_salary() const override { 
    std::cout << 
      "Software Engineer " << get_name() << 
      "'s salary is " << get_salary() << std::endl 
    << std::endl; 
  }
};

int main() {
  SoftwareEngineer Bob("Bob", 250.0);
  Courier Alice("Alice", 300.0);

  Bob.print_salary();
  Alice.print_salary();

  return 0;
}