#pragma once

#include <string>

class Course
{
private:
  std::string name;
  int units;
public:
  Course(std::string n, int u) { name = n; units = u;}
  std::string getName() { return name; }
  void setName(std::string n) { name = n; }
  int getUnits() { return units; }
  void setUnits(int u) { units = u; }
};