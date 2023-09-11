#pragma once
#include "course.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>    
#include <vector>

class Student
{
protected:
  std::string collegeChoice;
  std::string collegeMajor;
  std::vector<Course> collegeClasses;
  int collegeUnits;

public:
	Student();      
  Student(std::string, std::string, int, std::vector<Course>);
  void setCollege(std::string c);
  void setMajor(std::string m);
  void setUnits(int u);
  void setClasses(std::vector<Course> cl);
  std::string getCollege();
  std::string getMajor();
  int getUnits();
  std::vector<Course> getClasses();
};