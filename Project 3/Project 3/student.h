#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <string>
using namespace std;

//----------------------------------------------------------------------
// class student
//----------------------------------------------------------------------
// A simple class to describe a student, with a first and last name.
// Also a student id.
//----------------------------------------------------------------------

class student {
public:

	student();
	void setID(int newID);
	void setFirst(string newFirst);
	void setLast(string newLast);
	int getID();
	string getFirst();
	string getLast();
	void print();

private:

	int id;
	string first, last;
	
};