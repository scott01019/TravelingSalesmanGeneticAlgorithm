#include "city.h"

#include <math.h>

//  Pupose: Equality operator for City objects
//  Inputs: const reference to a City object to be compared
//  Outputs: true if the objects have the same coordinates
//  false if the objects have different coordinates
bool City::operator==(const City &rhs) const {
  if (this->x_ == rhs.x_ && this->y_ == rhs.y_) return true;
  else return false;
}

//  Name: Distance
//  Purpose: Get distance between current City and City parameter
//  Inputs: const reference to City object to get distance between
//  Ouputs: float value of the distance between current City and parameter City
float City::Distance(const City &city) const {
  float x = this->x_ - city.x_;
  float y = this->y_ - city.y_;
  return sqrt(static_cast<float>(x * x + y * y));
}