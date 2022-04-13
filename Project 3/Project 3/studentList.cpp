#include "studentList.h"
#include <fstream>

const int NOT_FOUND = -1;


//----------------------------------------------------------------------
//						constructor studentList
//----------------------------------------------------------------------
studentList:: studentList(){

	numStudents = 0;

};

//----------------------------------------------------------------------
//							getNumStudents
//----------------------------------------------------------------------
int studentList::getNumStudents(){
	return numStudents;
};

//----------------------------------------------------------------------
//							getStudent
//----------------------------------------------------------------------
student studentList::getStudent(int IDnum){
	
	for (int i = 0; i < numStudents; i++) {
		if (IDnum == stu[i].getID()) {
			return stu[i];
		}
	}
	return student();
};

//----------------------------------------------------------------------
//								read
//----------------------------------------------------------------------
void studentList::read(){
	
	string last;
	string first;
	int ID;

	ifstream fin("students.txt");
	
	if (fin.fail()) {
		cout << "Unable to open students.txt" << endl; \
			numStudents = 0;
	}
	else {
		
		fin >> numStudents;
		
		for (int i = 0; i < numStudents; i++) {
			
			fin >> ID >> first >> last;
			stu[i].setID(ID);
			stu[i].setFirst(first);
			stu[i].setLast(last);
			
		}

		fin.close();
	}
	

};

//----------------------------------------------------------------------
//								 print
//----------------------------------------------------------------------
void studentList::print(){

	cout << "=========" << " Student List " << "(" << numStudents << ") " << "=========" << endl;
	cout << " ID# " << "Last Name      " << " " << "First Name" << endl;
	cout << "----- " << "--------------- " << "---------------" << endl;
	for (int i = 0; i < numStudents; i++) {
		stu[i].print();
	}

};