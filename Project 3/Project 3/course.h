#pragma once
#include <iomanip>
#include <iostream>
using namespace std;
//----------------------------------------------------------------------
// class course
//----------------------------------------------------------------------
// A simple class to describe a course, with an id, department, number of
// hours and the title of it.
//----------------------------------------------------------------------


class course {
public:
	course();
	void set(int newID, string newDept, string newNum, int newHours, string newTitle);
	int getID();
	string getDept();
	string getNum();
	int getHours();
	string getTitle();
	void print();
	
private:
	int ID;
	string dept;
	string num;
	int numHours;
	string title;
};

