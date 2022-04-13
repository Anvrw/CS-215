
#include "courseCatalog.h"
#include<string>

//----------------------------------------------------------------------
//						constructor catalog
//----------------------------------------------------------------------
catalog::catalog() {
	numCourses = 0;

};
//----------------------------------------------------------------------
//								read
//----------------------------------------------------------------------
void catalog::read(){

	int ID;
	string dept;
	string num;
	int numHours;
	string title;
	

	ifstream fin("courses.txt");
	if (fin.fail()) {
		cout << "Unable to open courses.txt" << endl;
		numCourses = 0;
	}
	else {

		fin >> numCourses;
		
		for (int i = 0; i < numCourses; i++) {

			fin >> ID >> dept >> num >> numHours; getline(fin, title);
			clist[i].set(ID, dept, num, numHours, title);
			
		}
		fin.close();
	}
};
//----------------------------------------------------------------------
//								getCourse
//----------------------------------------------------------------------
course catalog::getCourse(int IDnum){
	int found = NOT_FOUND;
	course c;
	int idCheck;

	for (int i = 0; i < numCourses; i++) {

		idCheck = clist[i].getID();

		if (idCheck == IDnum) {
			found = i;
		}
	}
	if (found == NOT_FOUND) {
		return c;
	}
	else {
		return clist[found];
	}

};
//----------------------------------------------------------------------
//								print
//----------------------------------------------------------------------
void catalog::print(){
	cout << "=========" << " Course List " << "(" << numCourses << ") " << "=========" << endl;
	cout << " ID#  Dept Num  Hr Title" << endl;
	cout << "----- ---- ---- -- -----------------------------" << endl;
	for (int i = 0; i < numCourses; i++) {
		clist[i].print();
	}
};
