#pragma once
#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
//#include <time.h>

namespace Character {

	enum Character_Class {
		BARBARIAN = 0,
		BARD,
		CLERIC,
		DRUID,
		FIGHTER,
		MONK,
		PALADIN,
		RANGER,
		ROGUE,
		SORCERER,
		WIZARD
	};

	enum Abilities {

		STRENGTH = 0,
		DEXTERITY,
		CONSTITUTION,
		INTELLIGENCE,
		WISDOM,
		CHARISMA
	};

	struct EquipmentSlots {
		// Equiped items must be changed to pointers to item data type
		int armor{};
		int shield{};
		int weapon{};
		int boots{};
		int ring{};
		int helmet{};
	};

	class Character {
	public:
		Character();
		void Print_Character_Sheet();
		const int Hit_Points() { return hit_points; };
		const int Attack_Bonus() { return attack_bonus; };
		const int Modifier(int t_ability) { return ability_modifiers[t_ability]; };
		const int Proficiency_Bonus() { return proficiency_bonus; };


	private:
		//Default name
		std::string name{ "Cirian" };
		Character_Class character_class{};
		int level;
		//Use 'Ability' enum to index to desired ability score
		int ability_scores[6]{};
		//Use 'Ability' enum to index to desired ability score
		int ability_modifiers[6]{};
		EquipmentSlots equipment_slots{};
		int hit_points{};
		int natural_armour_class{};
		int armour_class{};
		int attack_bonus{};
		int damage_bonus{};
		int proficiency_bonus{};
		// std::vector<Item> inventory{};
		std::string get_class_name();
	};
}