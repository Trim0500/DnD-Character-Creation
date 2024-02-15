#ifndef DICE_H
#define DICE_H

// #include <time.h>
#include <ctime>
#include <iostream>
#include <regex>

using namespace std;


static regex DICE("([0-9]+)d(4|6|8|10|12|20|100)((?:\\+|-)[0-9]*)*");
class Dice {
public:
	Dice(string query);
	Dice();
	static int roll(string query);
	int roll();
	void add_die();
	void add_die(int amount);
private:
	int leading_multiplier=1;
	int die_sides=4;
	int addition=0;
};
Dice::Dice(string query){
	smatch sm; // rename variables
	if (!regex_search(query, sm, DICE)) {
		string e = "Query '" + query +  "' is invalid\n";
		throw invalid_argument(e);
	}
	if (sm[3].matched) {
		const string s = sm[3];
		if (s != ""){
			this->addition = stoi(s);
		}
	}
	string leading_multiplier_string = sm[1];
	string die_sides_string = sm[2];
	this->leading_multiplier = stoi(leading_multiplier_string);
	this->die_sides = stoi(die_sides_string);

}
int Dice::roll(){
	int rolls = 0;
	for (int i = 0; i < leading_multiplier; i++){
		rolls += (rand() % die_sides + 1); 
	}
	return rolls + addition;
}
Dice::Dice() {
	srand(time(nullptr));
}
int Dice::roll(string query){
	smatch sm; // rename variables
	if (!regex_search(query, sm, DICE)) {
		string e = "Query '" + query +  "' is invalid\n";
		throw invalid_argument(e);
	}
	int addition = 0;
	int rolls = 0;
	if (sm[3].matched) {
		const string s = sm[3];
		if (s != ""){
			addition = stoi(s);
		}
	}
	string leading_multiplier_string = sm[1];
	string die_sides_string = sm[2];
	int leading_multiplier = stoi(leading_multiplier_string);
	int die_sides = stoi(die_sides_string);
	for (int i = 0; i < leading_multiplier; i++){
		rolls += (rand() % die_sides + 1); 
	}
	return rolls + addition;
}
void Dice::add_die() {
	add_die(1);
}
void Dice::add_die(int amount) {
	this->leading_multiplier += amount;
}

#endif
