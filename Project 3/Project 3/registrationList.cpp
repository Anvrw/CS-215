#include "registrationList.h"
#include <string>
#include <fstream>

const int NOT_FOUND = -1;
const int MAX_COURSES = 10;
const int MAX_STUDENT_COURSES = 50;

//----------------------------------------------------------------------
//						constructor reglist
//----------------------------------------------------------------------
reglist::reglist(){ 
	
	numRegs = 0;

};

//----------------------------------------------------------------------
//						getNumRegistrations
//----------------------------------------------------------------------
int reglist::getNumRegistrations() {
	return numRegs;
};

//----------------------------------------------------------------------
//								read
//----------------------------------------------------------------------
void reglist::read() { 

	string sentinal_array = "END";
	int stuID;
	int courseID;
	string termName;
	int i = 0;

	ifstream fin ("regsin.txt");
	if (fin.fail()) {
		cout << "Unable to open regsin.txt" << endl;
	}
	else {

		fin >> stuID >> courseID >> termName;

		rlist[i].setCourseID(courseID);
		rlist[i].setStuID(stuID);
		rlist[i].setTerm(termName);

		numRegs++;

		i++;

		while (termName != sentinal_array) {
			fin >> stuID >> courseID >> termName;

			rlist[i].setCourseID(courseID);
			rlist[i].setStuID(stuID);
			rlist[i].setTerm(termName);
				
			numRegs++;
			
			i++;
		}
		fin.close();
	}
}

//----------------------------------------------------------------------
//								write
//----------------------------------------------------------------------
void reglist::write() { 
	ofstream fout;
	string outputFile = "regsout.txt";

	fout.open(outputFile);

	if (fout.fail()) {
		cout << "Unable to open " << outputFile;
	}
	else {

		sort();

		for (int i = 0; i < numRegs; i++) {
			fout << rlist[i].getStuID() << " " << rlist[i].getCourseID() << " " << rlist[i].getTerm() << endl;
		}

		cout << "Registrations written to file." << endl;

		

	}
	fout.close();
};

//----------------------------------------------------------------------
//							addRegistrations
//----------------------------------------------------------------------
bool reglist::addRegistration(int newStuID, int newCourseID, string newTerm) {

	if (numRegs < MAX_REGS) {
		registration r;
		registration rgate;
		r.setStuID(newStuID);
		r.setCourseID(newCourseID);
		r.setTerm(newTerm);
		rgate = rlist[numRegs - 1];
		rlist[numRegs - 1] = r;
		rlist[numRegs] = rgate;
		numRegs++;
		return true;
	}
	else {
		return false;
	}
};

//----------------------------------------------------------------------
//								search
//----------------------------------------------------------------------
int reglist::search(int newStuID, int newCourseID, string newTerm) {

	

	for (int i = 0; i < numRegs; i++) {
		if (newStuID == rlist[i].getStuID()) {
			if (newCourseID == rlist[i].getCourseID()) {
				if (newTerm == rlist[i].getTerm()) {
					return i;
				}
			}
		}
	}
	return NOT_FOUND;

};

//----------------------------------------------------------------------
//							dropRegistrations
//----------------------------------------------------------------------
bool reglist::dropRegistration(int newStuID, int newCourseID, string newTerm) {
	int searchValue = search(newStuID, newCourseID, newTerm);
	if (searchValue != NOT_FOUND) {
		for (int i = searchValue; i < numRegs; i++) {
			rlist[i] = rlist[i + 1];
		}
		numRegs--;
		return true;
	}
	else {
		return false;
	}
};

//----------------------------------------------------------------------
//								getSchedule
//----------------------------------------------------------------------
int reglist::getSchedule(int newStuID, string newTerm, int courseIDs[]) {
	int numCourseIDs = 0;
	int stuIDCheck;
	string termCheck;

	for (int i = 0; i < numRegs; i++) {

		stuIDCheck = rlist[i].getStuID();
		termCheck = rlist[i].getTerm();

		if (stuIDCheck == newStuID && termCheck == newTerm) {
			courseIDs[numCourseIDs] = rlist[i].getCourseID();
			numCourseIDs++;
		}
	}
	return numCourseIDs;
};

//----------------------------------------------------------------------
//								getRoster
//----------------------------------------------------------------------
int reglist::getRoster(int newCourseID, string newTerm, int stuIDs[]) {
	int numStuIDs = 0;
	int courseIDCheck;
	string termCheck;


	for (int i = 0; i < numRegs; i++) {

		courseIDCheck = rlist[i].getCourseID();
		termCheck = rlist[i].getTerm();

		if (courseIDCheck == newCourseID && termCheck == newTerm) {
			stuIDs[numStuIDs] = rlist[i].getStuID();
			numStuIDs++;
		}
	}
	return numStuIDs;
};

//----------------------------------------------------------------------
//								sortkey
//----------------------------------------------------------------------
string reglist::sortkey(registration r) {
	return to_string(r.getStuID()) + r.getTerm() + to_string(r.getCourseID());
};

//----------------------------------------------------------------------
//								sort
//----------------------------------------------------------------------
void reglist::sort() { 
	string sortKey1;
	string sortKey2;

	for (int i = 0; i < numRegs - 2; i++) {

		sortKey1 = sortkey(rlist[i]);

		for (int j = i + 1; j < numRegs - 1; j++) {
			
			sortKey2 = sortkey(rlist[j]);

			if (sortKey1 > sortKey2) {
				registration reg = rlist[i];
				rlist[i] = rlist[j];
				rlist[j] = reg;
			}
		}
	}
};

//----------------------------------------------------------------------
//								print
//----------------------------------------------------------------------
void reglist::print() { 
	cout << "reglist::print() --------------";
	for (int i = 0; i < numRegs; i++) {
		rlist[i].print();
	}
	cout << "regList::print: #regs = " << numRegs << endl;
};