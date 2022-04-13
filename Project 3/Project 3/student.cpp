
#include <iomanip>
#include "student.h"


//----------------------------------------------------------------------
// constructor student
//----------------------------------------------------------------------
student :: student(){ 

	id = 0;
	first = "";
	last = "";

};

//----------------------------------------------------------------------
//				seters for ID, first name, and last name
//----------------------------------------------------------------------
void student::setID(int newID){
	id = newID;
};
void student::setFirst(string newFirst){
	first = newFirst;
};
void student ::setLast(string newLast){
	last = newLast;
};

//----------------------------------------------------------------------
//					geters for ID, First, and Last 
//----------------------------------------------------------------------
int student::getID(){
	return id;
};
string student::getFirst(){
	return first;
};
string student::getLast(){
	return last;
};

//----------------------------------------------------------------------
//								print
//----------------------------------------------------------------------
void student::print(){
	cout << setw(5) << id << " " << setw(20) << last << " " << setw(15) << first << endl;
};