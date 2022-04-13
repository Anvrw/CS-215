#include "CRAPP.h"

const int MAX_STUDENT_PER_COURSE = 50;
const int MAX_COURSES_PER_STUDENT = 10;

const char eXit = 'X';
const char add = 'A';
const char drop = 'D';
const char PC = 'P';

const char Register = 'R';
const char CourseRoster = 'C';
const char PrintCatalog = 'P';
const char StudentList = 'S';
const char WriteRegs = 'W';
const char TermChange = 'T';

//----------------------------------------------------------------------
//							constructor crapp
//----------------------------------------------------------------------
crapp::crapp() {
	SL.read();
	cat.read();
	RL.read();
	currentTerm = "2020FA";
};

//----------------------------------------------------------------------
//								 go
//----------------------------------------------------------------------
void crapp::go() {

	char option = getMainMenuOption();

	while (option != eXit) {
		if (option == Register) {
			registerStudent();
		}
		else if (option == CourseRoster) {
			printRoster();
		}
		else if (option == PrintCatalog) {
			cat.print();
		}
		else if (option == StudentList) {
			SL.print();
		}
		else if (option == WriteRegs) {
			RL.write();
		}
		else if (option == TermChange) {
			changeTerm();
		}
		option = getMainMenuOption();
	}

	RL.write();
	cout << "Thank you for using our CRAPP! Merry Chrysler!" << endl;

};


//----------------------------------------------------------------------
//							askForStudent
//----------------------------------------------------------------------
student crapp::askForStudent() {

	int ID;
	student s;
	cout << "Enter student ID (0 to cancel): ";
	cin >> ID;
	s = SL.getStudent(ID);
	
	while (s.getID() == 0 && ID != 0) {
		cout << "Student ID " << s.getID() << " not found" << endl;
		cout << "Enter student ID (0 to cancel): ";
		cin >> ID;
		s = SL.getStudent(ID);
	}
	
	return s;
	
};


//----------------------------------------------------------------------
//								printRoster
//----------------------------------------------------------------------
void crapp::printRoster() {

	int studentIds[MAX_STUDENT_PER_COURSE];
	int numStudentIDs;
	student s;
	course c;
	int inputCourseID;
	
	cout << "Enter course ID: ";
	cin >> inputCourseID;

	c = cat.getCourse(inputCourseID);
	if (c.getID() == 0) {
		cout << "Invalid course ID" << endl;
	}
	else {
		cout << "-----------------------------------------------" << endl;
		cout << "Term: " << currentTerm << endl;
		c.print();
		cout << "-----------------------------------------------" << endl;
		cout << "STUID  LAST               FIRST" << endl;
		cout << "----- ------------------ --------------" << endl;
		numStudentIDs = RL.getRoster(inputCourseID, currentTerm, studentIds);
		for (int i = 0; i < numStudentIDs; i++) {
			s = SL.getStudent(studentIds[i]);
			s.print();
		}
		cout << "Number of students: " << numStudentIDs << endl;
		cout << "-----------------------------------------------" << endl;
	}

};


//----------------------------------------------------------------------
//							printSchedule
//----------------------------------------------------------------------
void crapp::printSchedule(student s) {

	int courseIds[MAX_COURSES_PER_STUDENT];
	int numCourses;
	int totalHours = 0;
	course c;

		cout << "-----------------------------------------------" << endl;
		cout << "Term: " << currentTerm << "  STUDENT: " << s.getLast() << ", " << s.getFirst() << " (" << s.getID() << ")" << endl;
		cout << "-----------------------------------------------" << endl;
		cout << "CRSID DEPT NUM  HR TITLE" << endl;
		cout << "----- ---- ---  -- ----------------------------" << endl;
		numCourses = RL.getSchedule(s.getID(), currentTerm, courseIds);
		for (int i = 0; i < numCourses; i++) {
			c = cat.getCourse(courseIds[i]);
			c.print();
			totalHours = totalHours + c.getHours();
		}
		cout << "Total Hours:    " << totalHours << endl;
		cout << "-----------------------------------------------" << endl;
	
};


//----------------------------------------------------------------------
//								 doAdd
//----------------------------------------------------------------------
bool crapp::doAdd(student s) {

	bool check;
	int courseId;
	course c;
	
	cout << "Enter course id to add:      ";
	cin >> courseId;

	c = cat.getCourse(courseId);
	if (c.getID() == 0) {
		cout << "Course ID Invalid" << endl;
		return false;
	}
	else {
		check = RL.addRegistration(s.getID(), courseId, currentTerm);
		if (check == false) {
			cout << "Course add failed!" << endl;
			return false;
		}
		else {
			cout << "Course added." << endl;
			return true;
		}
	}

};


//----------------------------------------------------------------------
//									doDrop
//----------------------------------------------------------------------
bool crapp::doDrop(student s) {

	bool check;
	int courseId;
	course c;

	cout << "Enter course id to drop:      ";
	cin >> courseId;

	c = cat.getCourse(courseId);
	if (c.getID() == 0) {
		cout << "Course ID Invalid" << endl;
	}
	else {
		check = RL.dropRegistration(s.getID(), courseId, currentTerm);
		if (check == false) {
			cout << "Student not registered for that course!" << endl;
			return false;
		}
		else {
			cout << "Course dropped." << endl;
			return true;
		}
	}

};


//----------------------------------------------------------------------
//							registerStudent
//----------------------------------------------------------------------
void crapp::registerStudent() {

	student s;
	char option;

	s = askForStudent();
	if (s.getID() != 0) {
		printSchedule(s);
		option = getOption("Drop, Add, Print Catalog, eXit? ", "DAPX");
		while (option != eXit) {
			if (option == drop) {
				doDrop(s);
			}
			else if (option == add) {
				doAdd(s);
			}
			else if (option == PC) {
				cat.print();
			}
			printSchedule(s);
			option = getOption("Drop, Add, Print Catalog, eXit? ", "DAPX");
		}
	}

};

//------------------------------------------------------------------------
//							getOption()
//------------------------------------------------------------------------
// prompt - the question to ask (ex: "Enter option: ")
// validOptions - a string of characters (ex: "ABCDEFG")
// returns: one of the valid characters (ex: 'D')
//------------------------------------------------------------------------
char crapp::getOption(string prompt, string validOptions) {
	string option;
	char opt;
	cout << prompt;
	cin >> option;
	opt = toupper(option[0]); // upper case of first char of entered value

	// while opt is not one of the chars in the validOptions string
	while (validOptions.find(opt) == string::npos) {
		cout << "Invalid option!\n";
		cout << prompt;
		cin >> option;
		opt = toupper(option[0]);
	}
	return opt;
} // getOption()

//------------------------------------------------------------------------
//						getMainMenuOption()
//------------------------------------------------------------------------
char crapp::getMainMenuOption() {
	// print the main menu
	cout << "\n============ CRAPP Main Menu =============\n";
	cout << "          Current Term: " << currentTerm << endl;
	cout << "R. Register Student\n";
	cout << "C. Course Roster\n";
	cout << "P. Print Catalog\n";
	cout << "S. Student List\n";
	cout << "W. Write registations\n";
	cout << "T. Term Change\n";
	cout << "X. Exit\n";
	return getOption("Enter menu option: ", "RCPSWTX");
} // getMainMenuOption()

//------------------------------------------------------------------------
//						        changeTerm()
//------------------------------------------------------------------------
void crapp::changeTerm() {
	cout << "Current term:   " << currentTerm << endl;
	cout << "Enter new term: ";
	cin >> currentTerm;
} // changeTerm()