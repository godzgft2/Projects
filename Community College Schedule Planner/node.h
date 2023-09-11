#pragma once
#include <vector>
#include <string>
#include "course.h"

class areaNode
{
private:
	std::string number; //number of general ed area
  std::vector<Course> courses;
	areaNode* next = nullptr;
public:
	areaNode() { number = "0"; next = nullptr;}
	areaNode(std::string d) { number = d; next = nullptr;}
	std::string getNumber() { return number;}
	
	friend class List;
};