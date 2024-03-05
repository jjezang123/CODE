#include<iostream>
#include<string>
#include<iomanip>
#include "Player.h"

using namespace std;
//--------------------------------------------
//	Constructor, Setters, Getters
//--------------------------------------------
Player::Player() { name = " ";  J_num = 0; num_g = 0; }
void Player::setJNum(int newJNum) { J_num = newJNum; }
void Player::setName(string newName) { name = newName; }
void Player::setNOG(int newGame) { num_g = newGame; }
int Player::getJNum() { return J_num; }
string Player::getName() { return name; }
int Player::getNumOfGames() { return num_g; }

//----------------------------------------------
//			    Calculations
//----------------------------------------------
void Player::all_threept() {
	for (int i = 0; i < num_g; i++) {
		tmade += three[i].getMade();
		tposs += three[i].getPoss();
	}
}
void Player::all_twopt() {
	for (int i = 0; i < num_g; i++) {
		tmade +=two[i].getMade();
		tposs += two[i].getPoss();
	}
}
void Player::all_ft() {
	for (int i = 0; i < num_g; i++) {
		tmade += one[i].getMade();
		tposs += one[i].getPoss();
	}
}
int Player::total_score(int num_g) {
	total[num_g] = (three[num_g].getMade() * 3) + (two[num_g].getMade()*2) + (one[num_g].getMade());
	return total[num_g];
}


//----------------------------------------------
//				    add Game
//----------------------------------------------
void Player::addGame(int i, int tpm, int tpp, int twm, int twp, int opm, int opp) {
	num_g++;
	three[i].setMade(tpm);
	three[i].setPoss(tpp);
	two[i].setMade(twm);
	two[i].setPoss(twp);
	one[i].setMade(opm);
	one[i].setPoss(opp);
	
}

//-----------------------------------------------
//			get Data for team::write()
//-----------------------------------------------
void Player::getDataForWrite(int i, int &tpm, int &tpp, int &twm, int &twp, int &opm, int &opp) { // this is used for write funcion in team.cpp ( just a different version of Player::addGame() )
	tpm = three[i].getMade();
	tpp = three[i].getPoss();
	twm = two[i].getMade();
	twp = two[i].getPoss();
	opm = one[i].getMade();
	opp = one[i].getPoss();
}

//----------------------------------------------
//				get Percentage for totals
//----------------------------------------------
int Player::getPCT(int m, int p) {
	if (p <= 0) {
		return 0;
	}
	else {
		return ((100 * m) / p);
	}
}


//-------------------------------------------------
//					print
//-------------------------------------------------
void Player::print() {			// used a given format
	
	cout << getName() << "  [" << getJNum() << "] \n";
	cout << "Game  3-Point FGs   2-Point FGs   Free Throws   Total\n";
	cout << "----  ------------  ------------  ------------  -----\n";
	for (int i = 0; i < num_g; i++) {
		cout << setw(4) << (i + 1); // change i to (i+1) if you like
		cout << right;
		//PRINT THE I'TH 3-POINTER: MM/AA (NNN%)
		three[i].print();  
		
		//PRINT THE I'TH 2-POINTER: MM/AA (NNN%)
		two[i].print();
	
		//PRINT THE I'TH FREE THROW: MM/AA (NNN%)
		one[i].print(); // << setw(5) << TOTAL_POINTS_FOR_THE_I'TH_GAME << "\n";
		
		//PRINT THE TOTAL
		cout << setw(5) << right << total_score(i);
		all_total += total_score(i);
		cout << endl;
	}
	cout << " ALL";
	//PRINT THE OVERALL 3-POINTER STAT:MM/AA (NNN%)
	all_threept();
	cout << setw(3) << right << tmade << "/" << setw(2) << right << tposs << " (" << setw(3) << right << getPCT(tmade, tposs) << "%) ";
	tmade = 0; tposs = 0;
	//PRINT THE OVERALL 2-POINTER STAT:MM/AA (NNN%)
	all_twopt();
	cout << setw(3) << right << tmade << "/" << setw(2) << right << tposs << " (" << setw(3) << right << getPCT(tmade, tposs) << "%) ";
	tmade = 0; tposs = 0;
	//PRINT THE OVERALL FREE THROW STAT:MM/AA (NNN%)
	all_ft();
	cout << setw(3) << right << tmade << "/" << setw(2) << right << tposs << " (" << setw(3) << right << getPCT(tmade, tposs) << "%) ";
	tmade = 0; tposs = 0;
	cout << setw(5) << right << all_total << endl << endl;
	
}
