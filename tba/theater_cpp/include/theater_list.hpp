#ifndef THEATER_LIST_HPP_
#define THEATER_LIST_HPP_

#include "theater.hpp"

namespace dov4k1n {

Theater empty_theater;

Theater some_theater(
  "some",
  "some",
  "some",
  0.0
);

Theater bolshoy(
  "Bolshoy",
  "Valery Georgiev",
  "Teatralnaya square, 1",
  5.0
);

Theater maly(
  "Maly",
  "Yuri Solomin",
  "Teatralny drive, 1c1",
  4.8
);

Theater mkht(
  "MKhT",
  "Konstantin Khabensky",
  "Kamergensky lane, 3",
  4.9
);

Theater vakhtangov(
  "Vakhtangov",
  "Kirill Krok",
  "Arbat street, 26",
  4.7
);

std::vector<Theater> theater_vect = {
  bolshoy, 
  maly, 
  mkht, 
  vakhtangov, 
  empty_theater, 
  some_theater
};

} // namespace dov4k1n

#endif // THEATER_LIST_HPP_