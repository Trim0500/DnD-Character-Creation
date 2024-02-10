#pragma once
#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
#include <vector>
#include <bitset>
#include "item.h"
#include "itemcontainer.h"

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

	class Character {
	public:
		Character();
		void Print_Character_Sheet();
		const int Hit_Points() { return hit_points; };
		const int Modifier(int t_ability) { return ability_modifiers[t_ability]; };
		const int Proficiency_Bonus() { return proficiency_bonus; };
		const int Sum_Levels();
		const std::bitset<11> Get_Class() { return character_class; };
		bool Levelup(Character_Class t_class);
		bool Equipe_Item(item::Item* t_item);
		const int Get_Armour_Class();
		const int Get_Attack_Bonus();


	private:
		//Default name
		std::string name{ "Cirian" };
		enum EquipmentSlots {
			// Equiped items must be changed to the item data type
			armor = 0,
			shield,
			weapon,
			boots,
			ring,
			helmet,
			belt,
			bag,
		};

		std::bitset<11> character_class;
		std::vector<int> level = std::vector<int> (11,0);
		//Use 'Ability' enum to index to the right ability score
		int ability_scores[6]{};
		//Use 'Ability' enum to index to desired ability score
		int ability_modifiers[6]{};
		int hit_points{};
		int damage_bonus{};
		int proficiency_bonus{};

		std::vector<item::Item*> equipment_slots = std::vector<item::Item*>(8);
		std::string Get_Class_Name(Character_Class t_class);
		std::string Get_Class_Name(int t_class);
		itemcontainer::ItemContainer inventory = itemcontainer::ItemContainer("Inventory", Backpack);

		
		//const int calculate_armour_class();
		const int calculate_proficiency();

	};
}