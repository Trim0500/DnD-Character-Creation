#include "..\Dice\Dice.h"

#include "DiceDemo.h"

void DiceDemo(){
	int r;
	Dice d;
	std::string query;
	
	//while (true) {
		std::cout << "Input dice to roll: (! to return to main menu)" << std::endl;
		std::cin >> query;
		///if (query.rfind("!", 0) == 0) { break; }
		std::cout << query;
		try {
			d = Dice(query);
			r = d.roll(query);
			std::cout << "You rolled " << r << std::endl;
		}
		catch (std::invalid_argument exc) {
			std::cout << "Invalid query" << std::endl;
		}
	//}
};