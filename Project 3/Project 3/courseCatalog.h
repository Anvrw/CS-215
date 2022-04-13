#pragma once
#include "course.h"
#include <fstream>

//----------------------------------------------------------------------
// class catalog
//----------------------------------------------------------------------
// A simple class to describe a course catalog that prints a catalog of
// courses.
//----------------------------------------------------------------------

const int MAX_COURSES = 20;
const int NOT_FOUND = -1;

class catalog {
public:

	catalog();
	void read();
	course getCourse(int IDNum);
	void print();


private:
	int numCourses;
	course clist[MAX_COURSES];
};