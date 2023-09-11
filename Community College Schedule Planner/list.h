#pragma once
#include "node.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

class List
{
private:
	areaNode* head = nullptr;
	areaNode* tail = nullptr;
public:
	List();
	~List();
	areaNode* getHead();
	void addAtEnd(std::string name, std::vector<Course> c);
  void pickGE(std::queue<Course>&, std::queue<Course>&);
};

areaNode* List::getHead()
{
	return head;
}

List::List()
{
	head = nullptr;
	tail = nullptr;
}

List::~List()
{
	areaNode* areaNodeptr;  //walks the list
	areaNode* nextareaNode;  //keeps next areaNode
	//start at beginning of list
	areaNodeptr = head;
	//loop while areaNodes to delete
	while (areaNodeptr != nullptr)
	{
		//deleting areaNode at areaNodeptr
		//but must save address of next areaNode first
		nextareaNode = areaNodeptr->next;
		//now delete areaNodeptr
		delete areaNodeptr;
		//move to next areaNode
		areaNodeptr = nextareaNode;
	}
}

void List::addAtEnd(std::string name, std::vector<Course> c)
{
	areaNode* newareaNode = new areaNode();
	newareaNode->number = name;
  newareaNode->courses = c;
	if (tail != nullptr)
		tail->next = newareaNode;
	tail = newareaNode;
	if (head == nullptr)
	{
		head = newareaNode;
	}
}

void List::pickGE(std::queue<Course>& GE, std::queue<Course>& majorPrep)
{
  areaNode* trav = head; //start at first area
  while(trav != nullptr)
  {
    std::cout << "Area " << trav->number << std::endl; //print out area number
    for (Course c : trav->courses)
    {
      std::cout << "Course name: " << c.getName() << " Units: " << c.getUnits() << std::endl;
    }

    if (trav == head) //at area 1
    {
      char CSU; //if they are going to a CSU
      std::cout << "You will need both English classes for your general ed." << std::endl;
      std::cout << "If you are going to a CSU, you will need the COMM class." << std::endl;
      std::cout << "Are you going to a CSU? (Y/N): ";
      std::cin >> CSU; //get input
      
      while (CSU != 'Y' && CSU != 'N')
      {
        std::cout << "That is not a valid input. Please re-enter (Y/N): ";
        std::cin >> CSU;
      }

      //either way, add both ENGL101A and 101C into the vector
      GE.push(trav->courses[0]);
      GE.push(trav->courses[1]);

      //only if it is CSU, add COMM
      if (CSU == 'Y')
      {
        GE.push(trav->courses[2]);
      }
    }
    else if (trav->number == "4-SOCIAL_BEHAVIORAL_SCIENCE")
    {

      for (int i = 0; i < 3; i++)
      {
        std::cout << std::endl;
        std::string choice; //user can pick a class they want
        std::cout << "What class would you like to take? (Name of course only): ";
        std::cin >> choice;
        
        //check that this course is in the vector
        bool found = false;
        int pos; //keep track of where the class they want to take is
        for (int i = 0; i < trav->courses.size(); i++)
        {
          if (trav->courses[i].getName() == choice)
          {
            found = true;
            pos = i;
          }
        }
        while (!found) //if the class isn't there, ask again
        {
          std::cout << "That class was not found :( Please re-enter: ";
          std::cin >> choice;
          for (int i = 0; i < trav->courses.size(); i++)
          {
            if (trav->courses[i].getName() == choice)
            {
              found = true;
              pos = i;
            }
          }
        }

        bool inside = false;
        bool duplicate = false;
        //check if the class is already in the vector as a major class
        for (int i = 0; i < majorPrep.size(); i++)
        {
          Course c = majorPrep.front();
          if (c.getName() == trav->courses[pos].getName())
          {
            inside = true;
          }
          majorPrep.pop();
          majorPrep.push(c);
        }
        //only if not inside, add the class
        if (!inside)
        {
          GE.push(trav->courses[pos]); //stores the class they want into the vector
        }
      }
    }
    else
    {
      std::cout << std::endl;
      std::string choice; //user can pick a class they want
      std::cout << "What class would you like to take? (Name of course only): ";
      std::cin >> choice;

      //check that this course is in the vector
      bool found = false;
      int pos; //keep track of where the class they want to take is
      for (int i = 0; i < trav->courses.size(); i++)
      {
        if (trav->courses[i].getName() == choice)
        {
          found = true;
          pos = i;
        }
      }
      while (!found)
      {
        std::cout << "That class was not found :( Please re-enter: ";
        std::cin >> choice;
        for (int i = 0; i < trav->courses.size(); i++)
        {
          if (trav->courses[i].getName() == choice)
          {
            found = true;
            pos = i;
          }
        }
      }

      bool inside = false;
      //check if the class is already in the vector as a major class
      for (int i = 0; i < majorPrep.size(); i++)
      {
        Course c = majorPrep.front();
        if (c.getName() == trav->courses[pos].getName())
        {
          inside = true;
        }
        majorPrep.pop();
        majorPrep.push(c);
      }

      //only if not inside, add the class
      if (!inside)
      {
        GE.push(trav->courses[pos]); //stores the class they want into the vector
      }
    }
    
    std::cout << std::endl;
    trav = trav->next;
  }
}