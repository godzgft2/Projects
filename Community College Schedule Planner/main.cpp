#include <iostream>
#include <string>
#include <locale>
#include <map>
#include <unordered_set>
#include <fstream>
#include <vector>
#include "student.h"
#include "node.h"
#include "course.h"
#include "list.h"
#include <queue>

struct College
{
  std::string name = ""; //name of college
  std::map<std::string, std::vector<Course>> majorClasses; //major classes for this college
};

//function declarations
std::string progChoice();
void storeColleges();
void askChoice(Student &studentCollege, std::vector<College> &Courses);
std::vector<College> createColleges();
void createFile(std::ifstream&, std::string&);
void createGenEd(List&);

int main() 
{
  std::vector<College> colleges;
  colleges = createColleges(); //store colleges and major classes
  List genEd; //will store all the general ed courses
  createGenEd(genEd);
  Student studentCollege; //check student.h for student functions
  //greet user and give description of program
  std::string choice = progChoice();
	while (choice == "Y")
	{
    askChoice(studentCollege, colleges); //saves variables to student class
    //show this student's information
    std::cout << "This is the college chosen: " << studentCollege.getCollege() << std::endl;
    std::cout << "This is the major chosen: " << studentCollege.getMajor() << std::endl;
    std::cout << "This is the max amount of units per semester: " << studentCollege.getUnits() << std::endl;
    std::cout << std::endl;

    //keep a vector of the classes the student has to take
    std::queue<Course> generalEds;
    std::queue<Course> majorPrep;

    int pos; //get position of the college the student wants to go to
    for (int i = 0; i < colleges.size(); i++)
    {
      if (studentCollege.getCollege() == colleges[i].name) //if at the same college
      {
        //then add all the major classes here to the vector
        for (Course c : colleges[i].majorClasses[studentCollege.getMajor()]) //gets the same major as the student is doing
        {
          majorPrep.push(c); //add this course to the major prep courses
        }
      }
    }

    //prints out all of your major classes
    for (int i = 0; i < majorPrep.size(); i++) //print all major prep classes
    {
      Course c = majorPrep.front();
      std::cout << c.getName() << " " << c.getUnits() << std::endl;
      majorPrep.pop();
      majorPrep.push(c); //add it back to the end of the queue
    }
    std::cout << "This is a list of your major classes. You may pick general ed classes that also coincide with your major classes." << std::endl;
    std::cout << "Keep in mind one class may only count for one general ed area." << std::endl;

    genEd.pickGE(generalEds, majorPrep); //get general eds student wants to take

    std::cout << std::endl;
    std::cout << "Theses are your major prep classes you will need:" << std::endl;
    for (int i = 0; i < majorPrep.size(); i++) //prints major prep
    {
      Course c = majorPrep.front();
      std::cout << c.getName() << " " << c.getUnits() << std::endl;
      majorPrep.pop();
      majorPrep.push(c);
    }
    std::cout << std::endl;
    std::cout << "These are your additional general ed classes:" << std::endl;
    for (int i = 0; i < generalEds.size(); i++) //prints major prep
    {
      Course c = generalEds.front();
      std::cout << c.getName() << " " << c.getUnits() << std::endl;
      generalEds.pop();
      generalEds.push(c);
    }

    std::cout << std::endl;

    int unitCap = 0; //keep the unitCap under the amount of the units the student wants to take
    int semesterCount = 1;
    while (majorPrep.size() > 0 || generalEds.size() > 0)
    {
      std::cout << "Semester " << semesterCount << ":" << std::endl;
      semesterCount++;
      while (unitCap + majorPrep.front().getUnits() + generalEds.front().getUnits() < studentCollege.getUnits() && generalEds.size() > 0 && majorPrep.size() > 0) //add the class into the semester only if doen't max unit cap
      {
        std::cout << majorPrep.front().getName() << " " << majorPrep.front().getUnits() << std::endl;
        std::cout << generalEds.front().getName() << " " << generalEds.front().getUnits() << std::endl;
        unitCap += majorPrep.front().getUnits();
        unitCap += generalEds.front().getUnits();
        majorPrep.pop();
        generalEds.pop();
      }
      while (unitCap + generalEds.front().getUnits() < studentCollege.getUnits() && generalEds.size() > 0)
      {
        std::cout << generalEds.front().getName() << " " << generalEds.front().getUnits() << std::endl;
        unitCap += generalEds.front().getUnits();
        generalEds.pop();
      }
      while (unitCap + majorPrep.front().getUnits() < studentCollege.getUnits() && majorPrep.size() > 0)
      {
        std::cout << majorPrep.front().getName() << " " << majorPrep.front().getUnits() << std::endl;
        unitCap += majorPrep.front().getUnits();
        majorPrep.pop();
      }
      std::cout << "TOTAL UNITS TAKEN: " << unitCap << std::endl;
      std::cout << std::endl;
      unitCap = 0;
    }
    
    //ask user to repeat or quit
    std::cout << "Would you like to run this program again? (Y/N) ";
    std::cin.ignore();
		std::getline(std::cin, choice); // if Y, will do this again
  }
  std::cout << "Thank you for using our program, goodbye! :)" << std::endl;
}

void createFile(std::ifstream& in, std::string& fileName)
{
	std::cout << "What is the name of the text file? ";
	std::cin >> fileName;
	//add ".txt" to end of the file name and use this for ifstream object
	fileName = fileName + ".txt";
	in.open(fileName);
	
	while (!in)
	{
		std::cout << "No such file exists, please re-enter(without .txt): ";
		std::cin >> fileName;
		fileName = fileName + ".txt";
		in.open(fileName);
	}
	std::cout << std::endl;
}

void createGenEd(List& genEd)
{
  //to get the text file containing details of colleges and major classes
  std::ifstream in; //create ifstream object to read in text from file
	std::cout << "FOR THE GENERAL ED TEXT FILE:" << std::endl;
	std::string genEdFileName;
	createFile(in, genEdFileName);

  std::string next = ""; //gets next word
  std::string areaNum = ""; //stores area number
  std::vector<Course> courses; //stores general ed courses for that area

  while (in >> next)
  {
    if (next == "AREA")
    {
      if (areaNum != "")
      {
        genEd.addAtEnd(areaNum, courses); //adds this area of classes to list
        courses.clear(); //resets vector of courses
      }
      in >> next;
      areaNum = next; //stores which area we are in
    }
    else
    {
      std::string courseName = next; //keeps the name of the course
      in >> next;
      int units = std::stoi(next); //keeps unit amount of that course
      Course c(courseName, units); //creates a course with this info
      courses.push_back(c); //adds this course to the set
    }
  }
  genEd.addAtEnd(areaNum, courses); //store the last area courses into list
}

std::vector<College> createColleges()
{
  //to get the text file containing details of colleges and major classes
  std::ifstream in; //create ifstream object to read in text from file
	std::cout << "FOR THE COLLEGE/MAJOR CLASSES TEXT FILE:" << std::endl;
	std::string collegeFileName;
	createFile(in, collegeFileName);

  //How can you access this vector outside of the functio
  std::vector<College> colleges; //holds all colleges
  College col; //create the college you will be storing into vector
	std::string collegeString; //to hold next string
  std::string major = ""; //stores current major
  std::vector<Course> courses; //stores courses for that major;

  while (in >> collegeString) //while still reading in new strings
  {
    if (collegeString == "SCHOOL")
    {
      if (col.name != "") //check to see if it is the first college
      {
        colleges.push_back(col); //store the complete college into vector
      }
      in >> collegeString; //get name of the college
      col.name = collegeString; //sets the name of the college to what came in
    }
    else if (collegeString == "MAJOR")
    {
      //before changing major, add this major and its classes to the map!
      if (major != "") //make sure it's not the first time
      {
        col.majorClasses[major] = courses;
        courses.clear(); //start a new set for the next major
      }
      in >> collegeString; //get major name
      major = collegeString; //we know we have hit the next major
    }
    else
    {
      std::string courseName = collegeString; //keeps the name of the course
      in >> collegeString;
      int units = std::stoi(collegeString); //keeps unit amount of that course  
      Course c(courseName, units); //creates a course with this info
      courses.push_back(c); //adds this course to the set
    }
  }
  //still have to add the last major [classes] to last college
  col.majorClasses[major] = courses;
  colleges.push_back(col); //and add last college to vector
  
  return colleges;
}

void askChoice(Student &studentCollege, std::vector<College> &Colleges) {
  std::string collegeChoice, choice, collegeMajor;
  int collegeUnits, collegeArray;
  bool errorCheck = 1;
  while (errorCheck)
	{
    std::cout << "Colleges: " << std::endl;
    for (College c : Colleges)
    {
        std::cout << c.name << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Hello! Enter a college you are transferring to: ";
    std::cin >> collegeChoice;
    //vector of college choices goes here
    for (int i = 0; i < Colleges.size(); i++) {
      if (Colleges[i].name == collegeChoice) {
        studentCollege.setCollege(collegeChoice);
        collegeArray = i;
        errorCheck = 0;
      }
    }
    if (errorCheck) {
      std::cout << "Chosen College: " << collegeChoice << std::endl;
      std::cout << "Sorry, we don't have that college on file" << std::endl;
      std::cout << "Available Colleges: ";
      for (int i = 0; i < Colleges.size(); i++) {
        std::cout << Colleges[i].name << " ";
      }
      std::cout << std::endl;
    }
    //loop through the college choices, if user input doesn't match, try again.
    //if good, errorCheck -> 0
	}
  errorCheck = 1;
  while (errorCheck)
	{
    std::cout << "MAJORS: " << std::endl;
    for (auto p = Colleges[1].majorClasses.begin(); p != Colleges[1].majorClasses.end(); p++)
		{ 
			std::cout << p->first << std::endl; 
		}
    std::cout << "Enter the major that you are taking: ";
    std::cin >> collegeMajor;
    
    //vector of college majors goes here
    for (auto p = Colleges[collegeArray].majorClasses.begin(); p != Colleges[collegeArray].majorClasses.end(); p++)
		{
     // std::cout << "major: " << p->first;
			if (p->first == collegeMajor) {
        studentCollege.setMajor(collegeMajor);
        errorCheck = 0;
      }
	  }
    if (errorCheck) {
      std::cout << "Sorry, we don't have that major on file" << std::endl;
      std::cout << "Available Majors: ";
       for (auto p = Colleges[collegeArray].majorClasses.begin(); p != Colleges[collegeArray].majorClasses.end(); p++)
		{
      std::cout << p->first << " ";
    }
      std::cout << std::endl;
      }
    //loop through the college majors, if user input doesn't match, try again.
    //if good, errorCheck -> 0
	}
  errorCheck = 1;
  std::cout << "What is the max amount of credits do you want per semester? (Max for Ohlone is 17.5) ";
  std::cin >> collegeUnits;
  while (errorCheck) {
    if (collegeUnits <= 17.5) {
      errorCheck = 0;
    } else if (collegeUnits > 17.5) {
      std::cout << "You will need counselor approval to overload " << collegeUnits << " units. \nDo you have it? (Y/N) ";
      std::cin.ignore();
      std::cin >> choice;
      if (choice == "N") {
        std::cout << "What is the max amount of credits do you want per semester? (Max for Ohlone is 17.5)";
        std::cin >> collegeUnits;
      } else if (choice == "Y") {
        errorCheck = 0;
      }
    }
  }
  studentCollege.setUnits(collegeUnits);
}

std::string progChoice()
{
	//ask user if they want to try
	std::cout << "This is a program aimed to create a transfer planner for you, using a college, a major, and number of units. \nWould you like to try it out? (Y/N) ";
	//create variable to keep track of what their input is
	std::string choice;
	std::cin >> choice;
	//validate their choice
	while (choice != "Y" && choice != "N")
	{
		std::cout << "That is not a valid input. Please input Y for yes or N for no: ";
		std::cin >> choice;
	}
	return choice;
}