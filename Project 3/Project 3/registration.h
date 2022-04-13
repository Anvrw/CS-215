#pragma once
#include <iomanip>
#include <iostream>
using namespace std;

//----------------------------------------------------------------------
// class registration
//----------------------------------------------------------------------
// A simple class to describe the registration and the student id, the
// course id, and the term of a class course.
//----------------------------------------------------------------------

class registration {
public:

	registration();
	
	void setStuID(int newID);
	void setCourseID(int newCourse);
	void setTerm(string newTerm);
	int getStuID();
	int getCourseID();
	string getTerm();
	void print();

private:
	int stuID;
	int courseID;
	string term;
};