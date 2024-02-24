/*!! \file Character.h
* \brief Header file containing Character functionality definitions
* The character creation is based off of the 5th edition Dungeons & Dragons! 
* Given the limited scope of assignment 1, several 5th edition specific features could not be implemented yet including
* but not limited to...
* 'Feats', 'Race', 'Class Features', 'Backgrounds', 'spells', 'skills', 'Armour, Weapon & tool proficiencies', 'Death saves', 'initiative' and 'saving throws'
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
#include "Dice.h"

/*! \namespace Character
* \brief namespace used to encapsulate 'Character' class functionality
*/
namespace Character {
	
	/*! \Enum Character_Class
	*  \brief Enum used to index various fields from the Character class
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
		Warlock = 10,
		Wizard = 11
	};
	
	constexpr std::bitset<12> isBarbarian	{ 0b0000'0000'0001 };
	constexpr std::bitset<12> isBard		{ 0b0000'0000'0010 };
	constexpr std::bitset<12> isCleric		{ 0b0000'0000'0100 };
	constexpr std::bitset<12> isDruid		{ 0b0000'0000'1000 };
	constexpr std::bitset<12> isFighter		{ 0b0000'0001'0000 };
	constexpr std::bitset<12> isMonk		{ 0b0000'0010'0000 };
	constexpr std::bitset<12> isPaladin		{ 0b0000'0100'0000 };
	constexpr std::bitset<12> isRanger		{ 0b0000'1000'0000 };
	constexpr std::bitset<12> isRogue		{ 0b0001'0000'0000 };
	constexpr std::bitset<12> isSorcerer	{ 0b0010'0000'0000 };
	constexpr std::bitset<12> isWarlock		{ 0b0100'0000'0000 };
	constexpr std::bitset<12> isWizard		{ 0b1000'0000'0000 };

	/*! \Enum Abilities_Stats
	*  \brief Enum used to index various fields from the Character class
	*/
	enum class Abilities_Stats {

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

	/*! 
	*  \brief Unordered map used to map values from item::CharacterStats TO Character::Abilities_Stats
	*/
	static const std::unordered_map<item::CharacterStats, Abilities_Stats> item_stat_TO_character_stat{
		{item::CharacterStats::Strength,Abilities_Stats::Strength},
		{item::CharacterStats::Dexterity,Abilities_Stats::Dexterity},
		{item::CharacterStats::Constitution,Abilities_Stats::Constitution},
		{item::CharacterStats::Intelligence,Abilities_Stats::Intelligence},
		{item::CharacterStats::Wisdom,Abilities_Stats::Wisdom},
		{item::CharacterStats::Charisma,Abilities_Stats::Charisma},
		{item::CharacterStats::ArmorClass,Abilities_Stats::ArmorClass},
		{item::CharacterStats::AttackBonus,Abilities_Stats::AttackBonus},
		{item::CharacterStats::DamageBonus,Abilities_Stats::DamageBonus},
		{item::CharacterStats::NA,Abilities_Stats::NA},
	};
	
	/*! \Enum Equipment_Slots
	*  \brief Enum used to index to fields from the Character class
	*/
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


	/*! \class Character
	* \brief Represents Character type entities
	*/
	class Character {
	public:
		/*! \fn Character()
		*  \brief Default character constructor that generates a character with random values for level, ability scores and maximum
		* hit points (By default will only give levels in the 'Fighter' class)
		*/
		Character();
		/*! \fn Character()
		*  \brief copy character constructor
		*/
		Character(const Character& t_character);
		/*! \fn Character()
		*  \brief Character Constructor. Initializes the character with one level in a given character class
		*  \param t_name: Name for the character 
		*  \param t_class: Character class the character will be given a level for
		*/
		Character(std::string t_name, Character_Class t_class);
		/*! \fn Character()
		*  \brief Character Constructor. Initializes the character with one level in a given character class. Sets ability scores randomly
		*  \param t_name: Name for the character
		*  \param t_class: Character class the character will be given a level for
		*/
		Character(Character_Class t_class);
		/*! \fn Character()
		*  \brief Character Constructor. Initializes the character with one level in a given character class
		*  \param t_name Name for the character
		*  \param t_class Character class the character will be given a level for
		*  \param t_ability_scores Set of desired ability scores {Strength,Dexterity,Constitution,Intelligence,Wisdom,Charisma}
		*/
		Character(std::string t_name, Character_Class t_class, const std::vector<int> &t_ability_scores);
		/*! \fn ID()
		*  \brief Unique Character ID
		*/
		const int ID() { return id; };
		/*! \fn Name()
		*  \brief Character name
		*/
		std::string& Name() { return name; };
		/*! \fn Print_Character_Sheet
		*  \brief Prints character data to consol
		*/
		void Print_Character_Sheet();
		/*! \fn Sum_Levels()
		*  \brief Returns sum total of all levels for this character 
		*  \return Returns const sum of elements in 'level' vector array
		*/
		const int Sum_Levels();
		/*! \fn Levels()
		*  \brief Returns the number of levels a chracter has taken in a corresponding class
		*  \param t_class: Any value from the Character::Character_Class enum
		*/
		const int Levels(Character_Class t_class) { return level[(int)t_class]; };
		/*! \fn Classes()
		*  \brief Used to perform bitwise comparision with 'isBarbarian', 'isBard', 'isCleric', 'isDruid', 'isFighter', 'isMonk',
		* 'isPaladin', 'isRanger', 'isRogue', 'isSorcerer' and 'isWizard' constexpr bitsets
		*  \return Returns const bitset<11> of 'character_class' field
		*/
		const std::bitset<12> Classes() { return character_class; };
		/*! \fn Levelup()
		*  \brief Levels up the the character by one level in a given class. Note that ability score bonuses given
		*  by items are not considered when checking if a character is able to mult-class
		*  \param t_class: Enum of type 'Character_Class' indicating which class a character will take a level in
		*  \return Returns true if levelup was performed succesfully, false otherwise
		*/
		bool Levelup(Character_Class t_class);
		/*! \fn Equip_Item()
		*  \brief Equips an item into the character's corresponding equipment slot. Item must be contained within the 'inventory'
		*  vector array to be equipped
		*  \param t_item: Item pointer to the object that the character will equip
		*  \return Returns true if equipping was performed succesfully, false otherwise
		*/

		

		bool Equip_Item(item::Item* t_item);
		/*! \fn Unequip_Item()
		*  \brief Equips an item into the character's corresponding equipment slot. Item must be contained within the 'inventory'
		*  vector array to be equipped
		*  \param t_item: Item pointer to the object that the character will equip
		*  \return Returns 'true' if equipping was performed succesfully, 'false' otherwise
		*/
		void Unequip_Item(Equipment_Slots t_slot);
		/*! \fn Max_Hit_Points()
		*  \return Returns const int to the maxium number of hitpoints for this character
		*/
		const int Max_Hit_Points() { return max_hit_points; };
		/*! \fn Hit_Points()
		*  \return Returns const int to the current number of hitpoints for this character
		*/
		const int Hit_Points() { return hit_points; };
		/*! \fn Receive_Damage()
		* \brief Inflict damage to character;
		* \param t_damage: amount of damage inflicted 
		*/
		void Receive_Damage(int t_damage);
		/*! \fn Receive_Damage()
		* \brief Heal character;
		* \param t_damage: amount of hit points restored
		*/
		void Receive_Healing(int t_heal);
		/*! \fn Alive()
		* \brief Checks if cahracter is alive;
		* \return Returns 'true' if hp > 0, 'false' otherwise 
		*/
		const bool Is_Alive();
		/*! \fn Modifier()
		*  \param t_ability: int/Ability enum indexing the desired modifier
		*  \return Returns const int to desired modifier. Modifier is detremined using ability scores and item bonuses
		*/
		const int Modifier(Abilities_Stats t_ability);
		/*! \fn Ability_Score_Natural()
		*  \param t_ability: int/Ability enum indexing the desired ability score
		*  \return Returns const int to desired ability score. Returned value does not take into account any item bonuses
		*/
		const int Ability_Score_Natural(Abilities_Stats t_ability);
		/*! \fn Ability_Score_Bonused()
		*  \param t_ability: int/Ability enum indexing the desired ability score
		*  \return Returns const int to desired ability score. Returned value does not take into account any item bonuses
		*/
		const int Ability_Score_Bonused(Abilities_Stats t_ability);
		/*! \fn Armour_Class()
		*  \brief Calculates and returns AC(armour class) based off a character's ability scores & equipped items
		*  \return Returns const int AC
		*/
		const int Armour_Class();
		/*! \fn Attack_Bonus()
		*  \brief Calculates and returns attack bonus based off a character's ability scores & equipped items | Proficiency Bonus + Strength Modifier + Enchantments
		*  \return Returns const int to attack bonus
		*/
		const int Attack_Bonus();
		/*! \fn Proficiency_Bonus()
		*  \brief Calculates and returns proficiency bonus based off a character's cumulative levels
		*  \return Returns const int to proficiency bonus
		*/
		const int Proficiency_Bonus();
		/*! \fn Damage_Bonus()
		*  \brief Calculates and returns damage bonus based off a character's strength and equipped items
		*  \return Returns const int to damage bonus
		*/
		const int Damage_Bonus();
		/*! \fn Inventory()
		*  \return Returns refrence to ItemContainer type object corresponding to the character's inventory
		*/
		itemcontainer::ItemContainer& Inventory() { return inventory; };
		/*! \fn Get_Equiped_Item()
		*  \return Returns pointer to item type object corresponding to the paramaters equipment slot. Retruns nullptr if no item is found
		*/
		const item::Item* Equipped_Items(Equipment_Slots t_item) { return equipment_slots.at(t_item); };
		/*! \fn Is_Multi_Classed()
		*  \brief Checks if the character is multi-classed with a particular character class
		*/
		bool Is_Multi_Classed(Character_Class t_class);
		/*! \fn Hit_Die_Pool()
		*  \return Returns a const refrence to the characters' hit die pool
		*/ 
		const std::unordered_map<Character_Class, Dice*>& Hit_Die_Pool() { return hit_die_pool; };

	private:

		static inline unsigned int id_gen{ 0 };
		const int id = id_gen++;

		std::string name{ "Cirian" };
		std::bitset<12> character_class;
		/*! 
		* Vector array corresponding to how many levels the character has taken in each class. Can be indexed using int/'Abilities' enum
		*/
		std::vector<int> level = std::vector<int> (12,0);
		/*!
		* Vector array corresponding to a character's ability scores. Can be indexed using int/'Abilities' enum
		*/
		std::vector<int> ability_scores = std::vector<int>(6);
		int max_hit_points{0};
		int hit_points{0};

		std::unordered_map<Character_Class, Dice*> hit_die_pool = {
			{Character_Class::Barbarian,  nullptr},
			{Character_Class::Bard, nullptr},
			{Character_Class::Cleric, nullptr},
			{Character_Class::Druid, nullptr},
			{Character_Class::Fighter, nullptr},
			{Character_Class::Monk, nullptr},
			{Character_Class::Paladin, nullptr},
			{Character_Class::Ranger, nullptr},
			{Character_Class::Rogue, nullptr},
			{Character_Class::Sorcerer, nullptr},
			{Character_Class::Warlock, nullptr},
			{Character_Class::Wizard,nullptr},

		};

		std::unordered_map<Equipment_Slots,item::Item*> equipment_slots;
    
		itemcontainer::ItemContainer inventory = itemcontainer::ItemContainer("Inventory", Backpack, 10);

		std::string Get_Class_String(Character_Class t_class);
		std::string Get_Class_String(int t_class);
		std::string Get_Abilities_String(Abilities_Stats t_abilities);
		std::string Get_Item_Type_String(item::ItemType t_type);
		std::string Get_Equipment_Slot_String(Equipment_Slots t_slot);

		bool Levelup_Barbarian();
		bool Levelup_Bard();
		bool Levelup_Cleric();
		bool Levelup_Druid();
		bool Levelup_Fighter();
		bool Levelup_Monk();
		bool Levelup_Paladin();
		bool Levelup_Ranger();
		bool Levelup_Rogue();
		bool Levelup_Sorcerer();
		bool Levelup_Warlock();
		bool Levelup_Wizard();

	};
}