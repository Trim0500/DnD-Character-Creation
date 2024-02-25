#include "Dice.h"

#include "DiceDemo.h"

void DiceDemo(){
	int r;
	Dice d;
	string query;
	while (true){ 
		cout << "Input dice to roll: (! to return to main menu)" << endl;
		cin >> query;
		if (query.rfind("!", 0)) {break;}
		try {
			d = Dice(query);
			r = d.roll(query);
			cout << "You rolled " << r << endl;
		} catch (invalid_argument exc) {
			cout << "Invalid query" << endl;
		}
	}
	
};