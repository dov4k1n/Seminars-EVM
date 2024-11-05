#ifndef INCLUDE_OBJECTS_CPP_
#define INCLUDE_OBJECTS_CPP_

#include <vector>

void showcase() {
  Car car_1(
    1, 
    "Wolkswagen", 
    "Tuareg",
    "Brown",
    70.0,
    5.0
  );

  Car car_2(
    2, 
    "Porsche", 
    "Cayenne",
    "Black",
    75.0,
    9.4
  );

  Car car_3(
    3, 
    "Audi", 
    "R8",
    "White",
    60.0,
    12.0
  );

  Truck truck_1(
    1,
    "Tesla",
    "Cybertruck",
    "Gray",
    100.0,
    5.0,
    10.0
  );

  Truck truck_2(
    2,
    "FAW",
    "J6 CA3250",
    "Black",
    110.0,
    11.0,
    6.0
  );

  Truck truck_3(
    3,
    "KamAZ",
    "43118",
    "Orange",
    130.0,
    3.0,
    7.0
  );

  // std::vector<Car> cars {car_1, car_2, car_3};
  // std::vector<Truck> trucks {truck_1, truck_2, truck_3};

  // std:vector<Car> cars;
  // cars.push_back(car_1);
  // cars.push_back(car_2);
  // cars.push_back(car_3);

  // std::vector<Truck> trucks;
  // trucks.push_back(truck_1);
  // trucks.push_back(truck_2);
  // trucks.push_back(truck_3);

  std::vector<Car> cars(3);
  cars[0] = car_1;
  cars[1] = car_2;
  cars[2] = car_3;

  std::vector<Truck> trucks(3);
  trucks[0] = truck_1;
  trucks[1] = truck_2;
  trucks[2] = truck_3;

  for (const Car& car : cars) {
    car.print_shifted();
    car.print_driving_range();
  }

  for (const Truck& truck : trucks) {
    truck.print_shifted();
    truck.print_transportation_cost();
  }
}

#endif // INCLUDE_OBJECTS_CPP_