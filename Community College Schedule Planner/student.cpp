#include "student.h"
#include <iostream>
#include <string>

Student::Student()
{
  collegeChoice = "null";
  collegeMajor = "null";
  collegeUnits = 0;
}

Student::Student(std::string c, std::string m, int u, std::vector<Course> classes){
  collegeChoice = c;
  collegeMajor = m;
  collegeUnits = u;
  collegeClasses = classes;
}

void Student::setCollege(std::string c) {
  collegeChoice = c;
}
void Student::setMajor(std::string m) {
  collegeMajor = m;
}
void Student::setUnits(int u) {
  collegeUnits = u;
}
void Student::setClasses(std::vector<Course> cl) {
  collegeClasses = cl;
}
std::string Student::getCollege() {
  return collegeChoice;
}
std::string Student::getMajor() {
  return collegeMajor;
}
int Student::getUnits() {
  return collegeUnits;
}
std::vector<Course> Student::getClasses() {
  return collegeClasses;
}