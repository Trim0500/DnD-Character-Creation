#ifndef DICE_H
#define DICE_H

// #include <time.h>
#include <ctime>
#include <iostream>
#include <regex>

using namespace std;


static regex DICE("([0-9]+)d(4|6|8|10|12|20|100)(?:\+([0-9]*))*");
class Dice {
public:
	Dice();
	int roll(string query);
};
Dice::Dice() {
	srand(time(nullptr));
}
int Dice::roll(string query){
	cmatch cm;
	smatch sm; // rename variables
	if (!regex_search(query, sm, DICE)) {
		return -1; // figure out proper error command
	}
	int addition = 0;
	int rolls = 0;
	// for debugging purposes
	if (sm.size()>3) {
		const std::string s = sm[3];
		// addition = sm[3];
		addition = stoi(s);
	}

	int leading_multiplier = stoi(sm[1]);
	int die_sides = stoi(sm[2]);
	
	for (int i = 0; i < leading_multiplier; i++){
		rolls += (rand() % die_sides + 1); 
	}
	

	return rolls + addition;
}

#endif