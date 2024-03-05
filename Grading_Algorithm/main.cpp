#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>

using namespace std;

//////////////////////////////////////////////////////////////////////////
//This is a tool developed in C++ that can be used for grading in class.//
//////////////////////////////////////////////////////////////////////////


// constants I need
const int max_s = 5;	// student and sets of scores
const int max_nos = 10;// maximum number of scores for each student
const int found = -1;

struct scores {		// set of variables for this program
	int made = 0;
	int poss = 0;
};

struct student {	// set of variables for this program
	int ID = 0;
	string Last;  // max 10 characters 
	string First; // max 15 characters
	int Num = 0;	// number of scores a student has. 
	scores sc[max_s];
};

void displayLogo() {		// displays logo

	cout << "+-----------------------------------------+\n"
		<< "|         Class Grading Algorithm         |\n"
		<< "|              by Jieon Jung              |\n"
		<< "+-----------------------------------------+\n";
}

void init(student s[], int& Num_students) {   // modifies the partial array of students
	
	Num_students = 0;				// initialize everything to zero

	for (int i = 0; i < max_s; i++) { // everything to empty
		s[i].ID = 0;
		s[i].Num = 0;
		s[i].Last = "";
		s[i].First = "";
		s[i].sc[i].made = 0;
		s[i].sc[i].poss = 0;
		
	}
	

}

/////////////////////////////////////////////////////////////////////////////////////
// It reads the file. If not, It initializes all to zero and starts without any given data
//////////////////////////////////////////////////////////////////////////////////////
void load(student s[], int& Num_students ) {
	ifstream fin;
	fin.open("grades.txt");				// open file
	if (fin.fail()) {					// case it fails to open
		cout << "No file detected... strating a new class.\n";
		init(s, Num_students);
		return;
	}
	else {		// read what is in written in the file

		fin >> Num_students;

		for (int i = 0; i < Num_students; i++) {
			fin >> s[i].ID >> s[i].First >> s[i].Last >> s[i].Num;
			for (int j = 0; j < s[i].Num; j++) {
				fin >> s[i].sc[j].made >> s[i].sc[j].poss;
			}
			cout << endl;
		}
	}
	fin.close();
}


////////////////////////////////////////////////////////////////////
// Write all the data to the output file at the end
////////////////////////////////////////////////////////////////////
void write(student s[], int& Num_students) {

	ofstream fout;
	fout.open("gradesout.txt");			// open file
	if (fout.fail()) {					// case it fails to open
		cout << "No file detected... strating a new class.\n";
		return;
	}	
	else {			// write every data into the file

		fout << Num_students;

		for (int i = 0; i < Num_students; i++) {
			fout << s[i].ID << s[i].First << s[i].Last << s[i].Num;
			for (int j = 0; j < s[i].Num; j++) {
				fout << s[i].sc[j].made << s[i].sc[j].poss;
			}
			cout << endl;
		}
		
	}

	fout.close(); // make sure it is closed
}


///////////////////////////////////////////////////////////////////////////////
// This will validate if the input char is one of the letters from given string
///////////////////////////////////////////////////////////////////////////////
bool ValidOrNot(char optin, string opt) {	
	bool TF;
	// we have 8 options
	if (optin == opt[0] || optin == opt[1] || optin == opt[2] || optin == opt[3] || optin == opt[4] || optin == opt[5] || optin == opt[6] || optin == opt[7]) {
		TF = true;
	}
	else {
		TF = false;
	}
	return TF; // return TF in terms of true and false
}


////////////////////////////////////////////////////////////////
// This function shows the option and takes input from teacher
////////////////////////////////////////////////////////////////
char getOption() {
	string UserInput;
	char choice;
	bool opt;
	
	cout << "A - Add Student          D - Drop Student\n"		// given options
		<< "V - View Student         E - Enter New Scores\n"
		<< "N - Sort by Name         P - Print class \n"
		<< "S - Sort class by avg    X - Exit        \n";
	cout << "Enter option: ";
	if (cin.peek() == '\n')cin.ignore();			// to bee clear
	getline(cin, UserInput);
	choice = toupper(UserInput[0]);
	opt = ValidOrNot(choice, "ADNVEPSX");			// invoke a function that will decide the validation of "choice"

	
	while (opt == false) {				// if choice isn't of the letters from the string, reask
		cout << "Invalid option, enter ADUVEPSX!\n";
		cout << "Enter option: ";
		if (cin.peek() == '\n')cin.ignore();
		getline(cin, UserInput);					// able to enter anything
		choice = toupper(UserInput[0]);				// but only read the first letter
		opt = ValidOrNot(choice, "ADNVEPSX");	
	}

	return choice;
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// add a new student including his or her ID, name, number of scores, and made/poss for each score
//////////////////////////////////////////////////////////////////////////////////////////////////
void addStudent(student s[], int& Num_students) {		


	if (Num_students >= max_s) {		// Do not exceed the max value
		cout << " No more students may be added. \n";
		return;
	}
	else {
		
		cout << "Enter student ID number: "; // enter all the data of the student
		cin >> s[Num_students].ID;
		cout << "Enter first and last name: ";
		cin >> s[Num_students].First >> s[Num_students].Last;
		cout << "Enter number of scores: ";
		cin >> s[Num_students].Num;


		while (s[Num_students].Num > max_s) {
			cout << "Invalid number of scores!\n";
			cout << "Don't make me ask you again. Enter the valid number of scores: ";
			cin >> s[Num_students].Num;
		}

		for (int i = 0; i < s[Num_students].Num; i++) {
			cout << "Enter score " << i+1 << " (made poss): ";
			cin >> s[Num_students].sc[i].made >> s[Num_students].sc[i].poss;
		}

		Num_students++; // number of student increase by 1

		cout << "New student added.\n";	// announce it is done
	}
}

////////////////////////////////////////////////////////////
// It searches the given array for a student with given ID
////////////////////////////////////////////////////////////
int search(student s[], int& ID) {
	int found = -1;
	for (int i = 0; i < max_s; i++) {    // search active
		if (ID == s[i].ID) {
			found = i;
		}
	}
	return found;			// return the found array number
}

/////////////////////////////////////////////////////////////////////////////
//	This function interacts with the user to perform a search by student ID
/////////////////////////////////////////////////////////////////////////////
int findStudent(student s[]) {
	int  ID;
	int found = -1;

	cout << "Enter student id number: ";		// ask the user for ID
	cin >> ID;

	found = search(s, ID);
	if (found == -1) {				// found or not?
		cout << "Student ID " << ID << " not found!" << endl;
	}
	
	return found;
}


///////////////////////////////////////////////////////////////////////////////////
// This function interacts with user to type an ID to drop a student from the list
// If a student is dropped, all the data related to the student is removed as well
//////////////////////////////////////////////////////////////////////////////////
void dropStudent(student s[], int& Num_students) {
	string rem = "";						// calling all the variables needed
	int remv = 0;
	int found;

	found = findStudent(s);					 // array number of the ID I want

	if (found > -1) {
			
		cout << s[found].First << " " << s[found].Last << " dropped." << endl;   // announce that this student is dropped

		s[found].First = rem;			// making all the values empty
		s[found].Last = rem;
		s[found].ID = remv;
		s[found].Num = remv;			
		s[found].sc[found].made = remv;
		s[found].sc[found].poss = remv;

		Num_students--;					// minus 1 from number of student when we drop a student

		for (int i = found; i < Num_students; i++) {
			s[i] = s[i + 1];
				// make this empty
		}
			
	}
	
}

///////////////////////////////////////////////////////////////////
// Calculate the average score for an asked student
/////////////////////////////////////////////////////////////////
double getAvg(student s[], int& askedStudent) {
	double avg;
	double sum = 0;
	double Num_s = s[askedStudent].Num;		// giving a name for Num of score
	for (int i = 0; i < Num_s; i++) {
		sum += (double(s[askedStudent].sc[i].made) / double(s[askedStudent].sc[i].poss));
	}		// making sure the values are in double
	avg = (sum / Num_s)*100;

	return avg;
}

///////////////////////////////////////////////////////////////////////
// This function determines the grade of student based on the average
///////////////////////////////////////////////////////////////////////
char getGrade(student s[], int& askedStudent){
	double avg = 0;
	char grade;
	avg = getAvg(s, askedStudent);     // Invoke a fuction to get avg
	
	if (avg >= 90) {				// which grade??
		grade = 'A';
	}
	else if (avg < 90 && avg >= 80) {
		grade = 'B';
	}
	else if (avg < 80 && avg >= 70) {
		grade = 'C';
	}
	else if (avg < 70 && avg >= 60) {
		grade = 'D';
	}
	else {
		grade = 'F';
	}

	return grade;		// it returns grade
}

///////////////////////////////////////////////////////////////////////////////////////////////
//	This function views all the data for one student including ID, name, avg, grade, and scores
///////////////////////////////////////////////////////////////////////////////////////////////
void viewStudent(student s[]) {

	int found;
	double avg;
	char grade;

	found = findStudent(s);		// Who do I want to view?
	
	if (found > -1 ) {
		avg = getAvg(s, found);		// invoke functions for the data needed
		grade = getGrade(s, found);
		// print all the data in the form I want
		cout << setprecision(3);	
		cout << "ID:   " << setw(4) << left << s[found].ID << "  Name:  " << setw(20) << left << (s[found].First + ", " + s[found].Last) << endl;
		cout << "Avg:  " << setw(4) << left << avg << "  Grade: " << setw(3) << left << grade << endl;
		cout << "Number of Scores:  " << s[found].Num << endl;
		cout << "Scores:		   ";
		for (int i = 0; i < s[found].Num; i++) {   // all scores of this student has
			cout << s[found].sc[i].made << "/" << s[found].sc[i].poss << "	";
		}
		cout << endl;
	}

}

///////////////////////////////////////////////////////////////////////////
//Prints a report of all studentsin the class in the format given.
////////////////////////////////////////////////////////////////////////////
void printClass(student s[], int& Num_students) {
	double avg;
	char grade;

	// print all the data
	cout << " ID   Name                   Avg  Grd  Scores                                   \n";
	cout << "----  --------------------  ----- ---  -----------------------------------------\n";
	for (int i = 0; i < Num_students; i++) {
		avg = getAvg(s, i);
		grade = getGrade(s, i);

		cout << setw(4) << s[i].ID << "  ";								// I've adjusted some of details to make sure it look clear in complier display 
		cout << setw(21) << left << (s[i].First + ", " + s[i].Last);
		cout << setw(5) << setprecision(3) << right << avg;
		cout << setw(4) << grade << " ";
		
		for (int j = 0; j < s[i].Num; j++) {
			cout << setw(3) << right << s[i].sc[j].made << "/ " << s[i].sc[j].poss << " " ;
		}
		cout << endl;
	}
}

///////////////////////////////////////////////////////////////////////////////
// This function swaps two elements in the array, identified by given indices
///////////////////////////////////////////////////////////////////////////////
void swap(student s[], int& cmp1, int& cmp2) {
	student t;

	t = s[cmp1];			//  applying the given format from the class
	s[cmp1] = s[cmp2];
	s[cmp2] = t;

}


////////////////////////////////////////////////////////////////
// Sort all the students alphabetically by their Last Name
/////////////////////////////////////////////////////////////////
void sortByName(student s[], int& Num_students) {
	string sort = "";
	string sort1 = "";

	for (int i = 0; i < Num_students; i++) {
		for (int j = i + 1; j < Num_students; j++) {
			sort = s[i].Last + s[i].First;			// give a temporary variable
			sort1 = s[j].Last + s[j].First;

			if (sort > sort1) {	// invoke swap function
				swap(s,i, j);
			}
		}
	}
	cout << "Class sorted by Name." << endl;
}

////////////////////////////////////////////////////////////////
// Sort all the students by their average score 
/////////////////////////////////////////////////////////////////
void sortByAvg(student s[], int& Num_students) {

	double a, b;

	for (int i = 0; i < Num_students; i++) {
		for (int j = i + 1; j < Num_students; j++) {
			a = getAvg(s, i);	// avg of the first student
			b = getAvg(s, j);	// avg of the next student

			if (a < b) {		// High to Low
				swap(s,i, j);	// invoke swap function
			}

		}
	}
	cout << "Class sorted by Average." << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// This option is used by the teacher to enter grades for all students in the class on the next assignment
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void enterScores(student s[], int& Num_students) {
	sortByName(s, Num_students);
	int poss;
	int num;
	
	cout << "Pts possible for the assignment? ";		// possible points?
	cin >> poss;

	cout << "Enter points made for each student: \n";
	for (int i = 0; i < Num_students; i++) {
		if (s[i].Num <= 5) {
			for (int j = i; j <= s[i].Num; j++) {
				cout << setw(4) << s[i].ID << setw(20) << (s[i].Last + ", " + s[i].First) << ":  ";
				s[i].sc[j].poss = poss;
				cin >> s[i].sc[j].made;

				/*
				for (int i = 0; i < Num_students; i++) {
			fin >> s[i].ID >> s[i].First >> s[i].Last >> s[i].Num;
			for (int j = 0; j < s[i].Num; j++) {
				fin >> s[i].sc[j].made >> s[i].sc[j].poss;
			}
			cout << endl;
		}*/
			}
		}
		else {
			cout << "Max scores exceeded!" << endl;

		}
	}
	cout << "Scores succesfully added." << endl;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// This is the main function that will call all the other functions from above
//////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
	student s[max_s];			// call all the variables and partial arrays and structs I need for the arguments
	scores n[max_nos];
	string name = "";
	char choice = '\0';
	int Num_students;		
	
	load(s, Num_students);		// reads the file

	while (choice != 'X') {		// create a while loop // run unless I want to quit by entering 'X'
		
			displayLogo();
			choice = getOption();

			if (choice == 'A') {
				addStudent(s, Num_students);
			}
			else if (choice == 'D') {
				dropStudent(s, Num_students);
			}
			else if (choice == 'V') {
				viewStudent(s);
			}
			else if (choice == 'E') {
				enterScores(s, Num_students);
			}
			else if (choice == 'P') {
				printClass(s, Num_students);
			}
			else if (choice == 'S') {
				sortByAvg(s, Num_students);
			}
			else if (choice == 'N') {
				sortByName(s, Num_students);
			
		}
	}
	write(s, Num_students);		// Write everything down when I'm done with this program
	cout << "Thanks for using May I Grade You!" << endl;
}
