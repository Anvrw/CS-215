#pragma once
#include "student.h"

const int MAX_STUDENTS = 20;

//----------------------------------------------------------------------
// class studentList
//----------------------------------------------------------------------
// A simple class to describe a student list that gets the number of
// students and the student in general.
//----------------------------------------------------------------------

class studentList {
public:
	studentList();
	int getNumStudents();
	student getStudent(int idNum);
	void read();
	void print();

private:
		student stu[MAX_STUDENTS];
		int numStudents;
};