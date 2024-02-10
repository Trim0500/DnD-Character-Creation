/* \file Character.h
* \brief Header file containing Character functionality definitions
*/
#pragma once
#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
#include <vector>
#include <bitset>
#include <map>
#include "item.h"
#include "itemcontainer.h"

/* \namespace Character
* \brief namespace used to encapsulate 'Character' class functionality
*/
namespace Character {

	enum class Character_Class {
		Barbarian = 0,
		Bard = 1,
		Cleric = 2,
		Druid = 3,
		Fighter = 4,
		Monk = 5,
		Paladin = 6,
		Ranger = 7,
		Rogue = 8,
		Sorcerer = 9,
		Wizard = 10
	};
	
	constexpr std::bitset<11> isBarbarian	{ 0b0000'0000'001 };
	constexpr std::bitset<11> isBard		{ 0b0000'0000'010 };
	constexpr std::bitset<11> isCleric		{ 0b0000'0000'100 };
	constexpr std::bitset<11> isDruid		{ 0b0000'0001'000 };
	constexpr std::bitset<11> isFighter		{ 0b0000'0010'000 };
	constexpr std::bitset<11> isMonk		{ 0b0000'0100'000 };
	constexpr std::bitset<11> isPaladin		{ 0b0000'1000'000 };
	constexpr std::bitset<11> isRanger		{ 0b0001'0000'000 };
	constexpr std::bitset<11> isRogue		{ 0b0010'0000'000 };
	constexpr std::bitset<11> isSorcerer	{ 0b0100'0000'000 };
	constexpr std::bitset<11> isWizard		{ 0b1000'0000'000 };

	enum Abilities {

		Strength = 0,
		Dexterity,
		Constitution,
		Intelligence,
		Wisdom,
		Charisma,
		ArmorClass,
		AttackBonus,
		DamageBonus,
		NA,
	};
	
	enum class Equipment_Slots {
		Armor = 0,
		Shield,
		Weapon,
		Boots,
		Ring,
		Helmet,
		Belt,
		Bag,
	};

	/* \class Character
	* \brief Represents Character type entities
	*/
	class Character {
	public:
		/* \fn Character()
		*  \brief Default character constructor that generates a character with random values for level, ability scores and maximum
		* hit points (By default will only give levels in the 'Fighter' class)
		*/
		Character();
		/* \fn Print_Character_Sheet
		*  \brief Prints character data to consol
		*/
		const int Get_ID() { return id; };
		const std::string& Get_Name() { return name; };
		void Print_Character_Sheet();
		/* \fn Sum_Levels()
		*  \brief Returns sum total of all levels for this character 
		*  \return Returns const sum of elements in 'level' vector array
		*/
		const int Sum_Levels();
		/* \fn Get_Class()
		*  \brief Used to perform bitwise comparision with 'isBarbarian', 'isBard', 'isCleric', 'isDruid', 'isFighter', 'isMonk',
		* 'isPaladin', 'isRanger', 'isRogue', 'isSorcerer' and 'isWizard' constexpr bitsets
		*  \return Returns const bitset<11> of 'character_class' field
		*/
		const std::bitset<11> Get_Class() { return character_class; };
		/* \fn Levelup()
		*  \brief Levels up the the character by one level in a given class (Not fully implemented yet)
		*  \param t_class: Enum of type 'Character_Class' indicating which class a character will take a level in
		*  \return Returns true if levelup was performed succesfully, false otherwise
		*/
		bool Levelup(Character_Class t_class);
		/* \fn Equip_Item()
		*  \brief Equips an item into the character's corresponding equipment slot. Item must be contained within the 'inventory'
		*  vector array to be equipped
		*  \param t_item: Item pointer to the object that the character will equip
		*  \return Returns true if equipping was performed succesfully, false otherwise
		*/
		bool Equip_Item(item::Item* t_item);
		/* \fn Get_Max_Hit_Points()
		*  \return Returns const int to the maxium number of hitpoints for this character
		*/
		const int Get_Max_Hit_Points() { return max_hit_points; };
		/* \fn Get_Hit_Points()
		*  \return Returns const int to the current number of hitpoints for this character
		*/
		const int Get_Hit_Points() { return hit_points; };
		/* \fn Get_Modifier()
		*  \param t_ability: int/Ability enum indexing the desired modifier
		*  \return Returns const int to desired modifier
		*/
		const int Get_Modifier(int t_ability);
		/* \fn Get_Ability_Score()
		*  \param t_ability: int/Ability enum indexing the desired ability score
		*  \return Returns const int to desired ability score
		*/
		const int Get_Ability_Score(int t_ability) { return ability_scores[t_ability]; };
		/* \fn Get_Armour_Class()
		*  \brief Calculates and returns AC(armour class) based off a character's ability scores & equipped items
		*  \return Returns const int AC
		*/
		const int Get_Armour_Class();
		/* \fn Get_Attack_Bonus()
		*  \brief Calculates and returns attack bonus based off a character's ability scores & equipped items | Proficiency Bonus + Strength Modifier + Enchantments
		*  \return Returns const int to attack bonus
		*/
		const int Get_Attack_Bonus();
		/* \fn Get_Proficiency_Bonus()
		*  \brief Calculates and returns proficiency bonus based off a character's cumulative levels and Strength/Dexterity modifer
		*  \return Returns const int to proficiency bonus
		*/
		const int Get_Proficiency_Bonus();
		/* \fn Get_Damage_Bonus()
		*  \brief Calculates and returns damage bonus based off a character's strength and equipped items
		*  \return Returns const int to damage bonus
		*/
		const int Get_Damage_Bonus();
		/* \fn Get_Inventory()
		*  \return Returns refrence to ItemContainer type object corresponding to the character's inventory
		*/
		itemcontainer::ItemContainer& Get_Inventory() { return inventory; };

	private:

		static inline unsigned int id_gen{ 0 };
		const int id = id_gen++;

		std::string name{ "Cirian" };
		std::bitset<11> character_class;
		/* 
		* Vector array corresponding to how many levels the character has taken in each class. Can be indexed using int/'Abilities' enum
		*/
		std::vector<int> level = std::vector<int> (11,0);
		/*
		* Vector array corresponding to a character's ability scores. Can be indexed using int/'Abilities' enum
		*/
		std::vector<int> ability_scores = std::vector<int>(6);
		int max_hit_points{};
		int hit_points{};

		std::vector<item::Item*> equipment_slots = std::vector<item::Item*>(8);
		std::string Get_Class_Name(Character_Class t_class);
		std::string Get_Class_Name(int t_class);
		itemcontainer::ItemContainer inventory = itemcontainer::ItemContainer("Inventory", Backpack);
		std::string Get_Equipment_Slot_Name(Equipment_Slots t_slot);

	
	};
}