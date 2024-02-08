#include "Character.h"

Character::Character::Character(){
	//create random number generator
	std::random_device rd;

	//Baseline class for assignment 1
	character_class = FIGHTER;
	//Generate level
	level = rd() % 20 + 1;
	//Generate ability scores
	for (int i{ 0 }; i < 6; i++) {
		//roll 3d6 for each ability score
		for (int j{ 0 }; j < 3; j++) {
			ability_scores[i] += rd() % 6 + 1;
		}
	}
	//Generate ability modifiers
	for (int i{ 0 }; i < 6; i++) {
		ability_modifiers[i] = std::floor(((float)(ability_scores[i] - 10) / 2));
	}
	//Generate hit points
	for (int i{ 0 }; i < level; i++) {
		hit_points += (rd() % 10 + 1)+ability_modifiers[CONSTITUTION];
	}
	//Generate base_armour_class
	natural_armour_class = (10 + ability_modifiers[DEXTERITY]);
	//Generate proficiency_bonus
	proficiency_bonus = std::lround((double)(level / 5.0)) + 2;
	//Generate attack_bonus (assume unarmed so use STRENGTH mod)
	attack_bonus = ability_modifiers[STRENGTH] + proficiency_bonus;
	//Generate damage_bonus(assume_unarmed at start so 0)
	damage_bonus = 0;
}

void Character::Character::Print_Character_Sheet()
{
	std::cout << std::right << std::setw(25) << "Name: " << name<<std::endl;
	std::cout << std::right << std::setw(25) << "Class: " << get_class_name() << std::endl;
	std::cout << std::right << std::setw(25) << "Level: " << level << std::endl;
	std::cout << std::right << std::setw(25) << "Proficiency Bonus : " << proficiency_bonus << std::endl;
	std::cout << std::right << std::setw(25) << "Attack Bonus (Unarmed) : " << attack_bonus << std::endl;
	std::cout << std::endl << std::right << std::setw(20) << "Ability Scores: " << std::endl << std::endl;
	std::cout << std::right << std::setw(20) << "Strength: " << std::left << std::setw(8) <<ability_scores[STRENGTH] << std::left << std::setw(1) << "Modifier: " << ability_modifiers[STRENGTH] << std::endl;
	std::cout << std::right << std::setw(20) << "Dexterity: " << std::left << std::setw(8) << ability_scores[DEXTERITY] << std::left << std::setw(1) << "Modifier: " << ability_modifiers[DEXTERITY] << std::endl;
	std::cout << std::right << std::setw(20) << "Constitution: " << std::left << std::setw(8) << ability_scores[CONSTITUTION] << std::left << std::setw(1) << "Modifier: " << ability_modifiers[CONSTITUTION] << std::endl;
	std::cout << std::right << std::setw(20) << "Intelligence: " << std::left << std::setw(8) << ability_scores[INTELLIGENCE] << std::left << std::setw(1) << "Modifier: " << ability_modifiers[INTELLIGENCE] << std::endl;
	std::cout << std::right << std::setw(20) << "Wisdom: " << std::left << std::setw(8) << ability_scores[WISDOM] << std::left << std::setw(1) << "Modifier: " << ability_modifiers[WISDOM] << std::endl;
	std::cout << std::right << std::setw(20) << "Charisma: " << std::left << std::setw(8) << ability_scores[CHARISMA] << std::left << std::setw(1) << "Modifier: " << ability_modifiers[CHARISMA] << std::endl;






}

std::string Character::Character::get_class_name()
{
	switch (this->character_class)
	{
	case BARBARIAN:
		return "Barbarian";
	case BARD:
		return "Bard";
	case CLERIC:
		return "Cleric";
	case DRUID:
		return "Druid";
	case FIGHTER:
		return "Fighter";
	case MONK:
		return "Monk";
	case PALADIN:
		return "Paladin";
	case RANGER:
		return "Ranger";
	case ROGUE:
		return "Rogue";
	case SORCERER:
		return "Sorcerer";
	case WIZARD:
		return "Wizard";
	default:
		return "Unknown Class";
	}
	
}
