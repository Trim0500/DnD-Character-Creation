#ifndef DICE_H
#define DICE_H

// #include <time.h>
#include <ctime>
#include <iostream>
#include <regex>
#include <string>

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
	std::string get_string();
private:
	int leading_multiplier=1;
	int die_sides=4;
	int addition=0;
};

#endif
