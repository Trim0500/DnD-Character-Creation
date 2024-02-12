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
#include <unordered_map>
#include "item.h"
#include "itemcontainer.h"

/* \namespace Character
* \brief namespace used to encapsulate 'Character' class functionality
*/
namespace Character {
	
	/* \Enum Character_Class
	*  \brief Enum used to index various level fields from the Character class
	*/
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

	enum class Abilities {

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

	static const std::unordered_map<item::CharacterStats, Abilities> item_stat_TO_character_abilities{
		{item::CharacterStats::Strength,Abilities::Strength},
		{item::CharacterStats::Dexterity,Abilities::Dexterity},
		{item::CharacterStats::Constitution,Abilities::Constitution},
		{item::CharacterStats::Intelligence,Abilities::Intelligence},
		{item::CharacterStats::Wisdom,Abilities::Wisdom},
		{item::CharacterStats::Charisma,Abilities::Charisma},
		{item::CharacterStats::ArmorClass,Abilities::ArmorClass},
		{item::CharacterStats::AttackBonus,Abilities::AttackBonus},
		{item::CharacterStats::DamageBonus,Abilities::DamageBonus},
		{item::CharacterStats::NA,Abilities::NA},
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
		/* \fn Character()
		*  \brief copy character constructor
		*/
		Character(const Character& t_character);
		/* \fn Character()
		*  \brief Character Constructor. Initializes the character with one level in a given character class
		*  \param t_name: Name for the character 
		*  \param t_class: Character class the character will be given a level for
		*/
		Character(std::string t_name, Character_Class t_class);
		/* \fn Character()
		*  \brief Character Constructor. Initializes the character with one level in a given character class. Sets ability scores randomly
		*  \param t_name: Name for the character
		*  \param t_class: Character class the character will be given a level for
		*/
		Character(Character_Class t_class);
		/* \fn Character()
		*  \brief Character Constructor. Initializes the character with one level in a given character class
		*  \param t_name Name for the character
		*  \param t_class Character class the character will be given a level for
		*  \param t_ability_scores Set of desired ability scores {Strength,Dexterity,Constitution,Intelligence,Wisdom,Charisma}
		*/
		Character(std::string t_name, Character_Class t_class, const std::vector<int> &t_ability_scores);
		/* \fn Character()
		*  \brief Character Constructor. Initializes the character with one level in a given character class
		*  \param t_name Name for the character
		*  \param t_class Character class the character will be given a level for
		*  \param t_ability_scores Set of desired ability scores {Strength,Dexterity,Constitution,Intelligence,Wisdom,Charisma}
		*  \param t_max_hit_points Desired maximum hit points
		*/
		Character(std::string t_name, Character_Class t_class, const std::vector<int>& t_ability_scores, int t_max_hit_points);


		const int ID() { return id; };
		const std::string& Name() { return name; };
		const std::string& Name(std::string);
		/* \fn Print_Character_Sheet
		*  \brief Prints character data to consol
		*/
		void Print_Character_Sheet();
		/* \fn Sum_Levels()
		*  \brief Returns sum total of all levels for this character 
		*  \return Returns const sum of elements in 'level' vector array
		*/
		const int Sum_Levels();
		/* \fn Levels()
		*  \brief Returns the number of levels a chracter has taken in a corresponding class
		*  \param t_class: Any value from the Character::Character_Class enum
		*/
		const int Levels(Character_Class t_class) { return level[(int)t_class]; };
		/* \fn Classes()
		*  \brief Used to perform bitwise comparision with 'isBarbarian', 'isBard', 'isCleric', 'isDruid', 'isFighter', 'isMonk',
		* 'isPaladin', 'isRanger', 'isRogue', 'isSorcerer' and 'isWizard' constexpr bitsets
		*  \return Returns const bitset<11> of 'character_class' field
		*/
		const std::bitset<11> Classes() { return character_class; };
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
		/* \fn Unequip_Item()
		*  \brief Equips an item into the character's corresponding equipment slot. Item must be contained within the 'inventory'
		*  vector array to be equipped
		*  \param t_item: Item pointer to the object that the character will equip
		*  \return Returns true if equipping was performed succesfully, false otherwise
		*/
		void Unequip_Item(Equipment_Slots t_slot);
		/* \fn Max_Hit_Points()
		*  \return Returns const int to the maxium number of hitpoints for this character
		*/
		const int Max_Hit_Points() { return max_hit_points; };
		/* \fn Hit_Points()
		*  \return Returns const int to the current number of hitpoints for this character
		*/
		const int Hit_Points() { return hit_points; };
		/* \fn Modifier()
		*  \param t_ability: int/Ability enum indexing the desired modifier
		*  \return Returns const int to desired modifier
		*/
		const int Modifier(Abilities t_ability);
		/* \fn Ability_Score()
		*  \param t_ability: int/Ability enum indexing the desired ability score
		*  \return Returns const int to desired ability score
		*/
		const int Ability_Score(Abilities t_ability);
		/* \fn Armour_Class()
		*  \brief Calculates and returns AC(armour class) based off a character's ability scores & equipped items
		*  \return Returns const int AC
		*/
		const int Armour_Class();
		/* \fn Attack_Bonus()
		*  \brief Calculates and returns attack bonus based off a character's ability scores & equipped items | Proficiency Bonus + Strength Modifier + Enchantments
		*  \return Returns const int to attack bonus
		*/
		const int Attack_Bonus();
		/* \fn Proficiency_Bonus()
		*  \brief Calculates and returns proficiency bonus based off a character's cumulative levels and Strength/Dexterity modifer
		*  \return Returns const int to proficiency bonus
		*/
		const int Proficiency_Bonus();
		/* \fn Damage_Bonus()
		*  \brief Calculates and returns damage bonus based off a character's strength and equipped items
		*  \return Returns const int to damage bonus
		*/
		const int Damage_Bonus();
		/* \fn Inventory()
		*  \return Returns refrence to ItemContainer type object corresponding to the character's inventory
		*/
		itemcontainer::ItemContainer& Inventory() { return inventory; };
		/* \fn Get_Equiped_Item()
		*  \return Returns pointer to item type object corresponding to the paramaters equipment slot. Retruns nullptr if no item is found
		*/
		const item::Item* Equipped_Items(Equipment_Slots t_item) { return equipment_slots.at(t_item); };


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

		std::unordered_map<Equipment_Slots,item::Item*> equipment_slots;
		//std::vector<item::Item*> equipment_slots = std::vector<item::Item*>(8);
		itemcontainer::ItemContainer inventory = itemcontainer::ItemContainer("Inventory", Backpack, 10);
		std::string Get_Class_Name(Character_Class t_class);
		std::string Get_Class_Name(int t_class);

		std::string Get_Abilities_Name(Abilities t_abilities);

		std::string Get_Item_Type_Name(item::ItemType t_type);

		std::string Get_Equipment_Slot_Name(Equipment_Slots t_slot);

	
	};
}