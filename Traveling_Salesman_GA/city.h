#ifndef CITY_H_
#define CITY_H_

//  A city class to represent a city the salesman travels two
class City {
public:
  //  constructos
  City() {}
  City(int x, int y) : x_(x), y_(y) {}

  //  methods
  bool operator==(const City &) const;
  float Distance(const City &) const;

  //  getters
  int x() const { return this->x_; }
  int y() const { return this->y_; }

  //  setters
  void set_x(int x) { this->x_ = x; }
  void set_y(int y) { this->y_ = y; }
private:
  int x_; //  x-coord
  int y_; //  y-coord
};

#endif  //  CITY_H_