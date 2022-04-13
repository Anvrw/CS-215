#pragma once
#include <iostream>
#include <iomanip>
#include "student.h"
#include "studentList.h"
#include "courseCatalog.h"
#include "registrationList.h"
#include "registration.h"
using namespace std;

//----------------------------------------------------------------------
// class crapp
//----------------------------------------------------------------------
// This class is the culmination of all other classes, it includes the
// student list, catalog, and registration list.
//----------------------------------------------------------------------

class crapp {
public:
	
	crapp();
	void go();
	
private:

	studentList SL;
	catalog cat;
	reglist RL;
	string currentTerm;

	student askForStudent();
	void printRoster();
	void printSchedule(student s);
	bool doAdd(student s);
	bool doDrop(student s);
	void registerStudent();
	char getOption(string prompt, string validOptions);
	char getMainMenuOption();
	void changeTerm();

};
