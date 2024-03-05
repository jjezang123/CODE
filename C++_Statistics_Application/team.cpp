#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include "team.h"
#include "Player.h"
#include "Statistics.h"

using namespace std;

//------------------------------------------------------
//                    Constructor
//------------------------------------------------------
team::team() {
	num_p = 0;
	num_g = 0;
}


//------------------------------------------------------
//                   print Report
//------------------------------------------------------
void team::printReport() {
	for (int i = 0; i < num_p; i++) {
		p[i].print();
	}
}

//------------------------------------------------------
//                    add Game
//------------------------------------------------------
void team::addGame() {
	
	int tpm, tpp, twm, twp, opm, opp = 0;
	
	if (num_g < MAX_G) {

		for (int i = 0; i < num_p; i++) {
			cout << "Enter stats for " << p[i].getName() << "[" << p[i].getJNum() << "]" << endl;
			cout << "3 Pointers (made attempted): ";
			cin >> tpm >> tpp;
			cout << "2 Pointers (made attempted): ";
			cin >> twm >> twp;
			cout << "Free throws (made attempted): ";
			cin >> opm >> opp;
			p[i].addGame((num_g), tpm, tpp, twm, twp, opm, opp);
		}
		cout << "Game Added. " << endl;
	}
	else {
		cout << "Max GAME exceeded." << endl;
	}


}

//-----------------------------------------------------
//				   search Player
//-----------------------------------------------------
int team::searchPlayer(int num) {
	int found = -1;
	for (int i = 0; i < num_p; i++) {
		if (num == p[i].getJNum()) {
			found = i;
		}
	}
	return found;
}

//-----------------------------------------------------
//					find player
//-----------------------------------------------------
int team::findPlayer() {
	int jersey;
	int found = -1;

	cout << "Enter player jersey number: ";
	cin >> jersey;

	found = searchPlayer(jersey);

	
	return found;
}

//------------------------------------------------------
//				   display Player
//------------------------------------------------------
void team::displayPlayer() {
	int found;

	found = findPlayer();

	if (found > -1){
	p[found].print();
	}
	else {
		cout << "Player not found!\n\n";
	}
}


//-----------------------------------------------------
//					remove player
//-----------------------------------------------------
void team::removePlayer() {
	string rem = "";
	int remv = 0;
	int found;
	found = findPlayer();
	

	if (found > -1) {
		num_p--;

		for (int i = found; i < num_p; i++) {
			p[i] = p[i + 1];				// overwirte the player so the previous player gets removed
		}
		cout << "Player removed." << endl;
	}
	else {
		cout << "Player not found!\n\n";
	}
}

//------------------------------------------------------
//					sort by name
//------------------------------------------------------
void team::sortByName() {
	string a = "";
	string b = "";
	Player t;
	for (int i = 0; i < num_p; i++) {
		for (int j = i + 1; j < num_p; j++) {
			a = p[i].getName();
			b = p[j].getName();

			if (a > b) {
				t = p[i];
				p[i] = p[j];
				p[j] = t;
			}
		}
	}
	cout << "Roster sorted by Name." << endl;
}

//------------------------------------------------------
//					sort by jersey
//------------------------------------------------------
void team::sortByJersey() {
	int a = 0;
	int b = 0;
	Player t;
	for (int i = 0; i < num_p; i++) {
		for (int j = i + 1; j < num_p; j++) {
			a = p[i].getJNum();
			b = p[j].getJNum();

			if (a > b) {
				t = p[i];
				p[i] = p[j];
				p[j] = t;
			}
		}
	}
	cout << "Roster sorted by Jersey Number." << endl;
}

//------------------------------------------------------
//                    read File
//------------------------------------------------------ 
void team::readFile() {
	int Jersey = 0;
	int tpm = 0, tpp = 0, twm = 0, twp = 0, opm = 0, opp = 0;
	string NAME;
	Player t;

	ifstream fin;
	fin.open("bballin.txt");
	if (fin.fail()) {
		cout << "No file detected..." << endl;
		// init
	}
	
	fin >> num_p >> num_g;


	for (int i = 0; i < num_p; i++) {
		fin >> Jersey;
		getline(fin, NAME);
		p[i].setJNum(Jersey);
		p[i].setName(NAME);
	
		for (int j = 0; j < num_g; j++) {
			fin >> tpm >> tpp >> twm >> twp >> opm >> opp;
			p[i].addGame(j, tpm, tpp, twm, twp, opm, opp);  // invoke addGame function to set the points for each player
		}
		
	}
	fin.close();
}

//-------------------------------------------------
//				      write
//-------------------------------------------------
void team::write() {
	int tpm = 0, tpp = 0, twm = 0, twp = 0, opm = 0, opp = 0;

	ofstream fout;
	fout.open("bballout.txt");
	if (fout.fail()) {
		cout << "unable to open the file" << endl;
	}
	else {
		fout << num_p << " "<< num_g << endl;	
		for (int i = 0; i < num_p; i++) {
			fout << p[i].getName() << "  [" << p[i].getJNum() << "]" << endl;
			for (int j = 0; j < num_g; j++){
				p[i].getDataForWrite(j, tpm, tpp, twm, twp, opm, opp);								// the same method I used for readFile
				fout << tpm <<" " << tpp  << " " << twm << " " << twp << " " << opm << " " << opp << endl;
			}
		}

	}
	fout.close();

	cout << "Thank you for using  BASKETBALL STATS SUPREME by Jieon Jung^^" << endl;
}
