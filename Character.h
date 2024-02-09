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
		const int Attack_Bonus() { return attack_bonus; };
		const int Modifier(int t_ability) { return ability_modifiers[t_ability]; };
		const int Proficiency_Bonus() { return proficiency_bonus; };
		const int Sum_Levels();
		const std::bitset<11> Get_Class() { return character_class; };
		bool Levelup(Character_Class t_class);
		bool Equipe_Item(item::Item* t_item);

	private:
		//Default name
		std::string name{ "Cirian" };
		struct EquipmentSlots {
			// Equiped items must be changed to the item data type
			item::Item* armor{};
			item::Item* shield{};
			item::Item* weapon{};
			item::Item* boots{};
			item::Item* ring{};
			item::Item* helmet{};
			item::Item* belt{};
			item::Item* bag{};
		};

		std::bitset<11> character_class;
		std::vector<int> level = std::vector<int> (11,0);
		//Use 'Ability' enum to index to the right ability score
		int ability_scores[6]{};
		//Use 'Ability' enum to index to desired ability score
		int ability_modifiers[6]{};
		int hit_points{};
		int armour_class{};
		int attack_bonus{};
		int damage_bonus{};
		int proficiency_bonus{};

		EquipmentSlots equipment_slots{};
		itemcontainer::ItemContainer inventory = itemcontainer::ItemContainer("Inventory", Backpack);
		std::string Get_Class_Name(Character_Class t_class);
		std::string Get_Class_Name(int t_class);

		/*
		int calculate_armour_class();
		int calculate_proficiency();
		int calculate_attack_bonus();
		*/

	};
}