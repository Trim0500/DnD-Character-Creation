#include "Character.h"
#include <iostream>
#include <random>

Character::Character(int t_level, CharacterClass t_class){
	int skill_points = (2 + ability_modifiers[intelligence]) * 4;
	//-add exception handeling for level && class
	character_class = t_class;
	level = t_level;
	//Generate ability scores
	for (int i{ 0 }; i < 6; i++) {
		//ability scores randomly generated between 1 & 18
		ability_scores[i] = rand() % 18 + 1;
	}
	//Calculate ability modifiers
	for (int i{ 0 }; i < 6; i++) {
		ability_modifiers[i] = std::floor((ability_scores[i] - 10) / 2);
	}
	//Calculate hit points
	
	//Character creation based on class 
	switch (character_class){
		case fighter:
			//Fighter class case 
			std::cout << "is fighter" << std::endl;
			break;
		default:
			std::cout << "INVALID CLASS" << std::endl;
			return;
	}
}
