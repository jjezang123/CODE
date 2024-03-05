#include<iostream>
#include<iomanip>
#include<fstream>
#include "Statistics.h"

using namespace std;

//--------------------------------------------
//   Constructor, setters, getters
//--------------------------------------------
Statistic::Statistic() {  made = 0; poss = 0; }
void Statistic::setMade(int newMade) { made = newMade; }
void Statistic::setPoss(int newPoss) { poss = newPoss; }
int Statistic::getMade() { return made; }
int Statistic::getPoss() { return poss; }

//---------------------------------------------
//					print
//---------------------------------------------
void Statistic::print() {
	cout << setw(3) << right << made << "/" << setw(2) << right << poss << " (" << setw(3) << right << getPCT() << "%) ";
}

//---------------------------------------------
//				get percentage
//---------------------------------------------
int Statistic::getPCT() {
	if (poss <= 0) {
		return 0;
	}
	else {
		return ((100 * made) / poss);
	}
}