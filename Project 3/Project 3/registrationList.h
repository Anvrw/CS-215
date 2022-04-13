#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include "registration.h"

const int MAX_REGS = 100;

//----------------------------------------------------------------------
// class reglist
//----------------------------------------------------------------------
// A simple class to describe a registration list that searches for the
// student and the schedule, this adds the registration, searching for
// the student, drop registration. This gets the schedule and roster and
// sorts them.
//----------------------------------------------------------------------

class reglist {
public:

	reglist();
	int getNumRegistrations();
	void read();
	void write();
	bool addRegistration(int newStuID, int newCourseID, string newTerm);
	int search(int newStuID, int newCourseID, string newTerm);
	bool dropRegistration(int newStuID, int newCourseID, string newTerm);
	int getSchedule(int newStuID, string newTerm, int courseIDs[]);
	int getRoster(int newCourseID, string newTerm, int stuIDs[]);
	string sortkey(registration r);
	void sort();
	void print();

private:

	registration rlist[MAX_REGS];
	int numRegs;

};