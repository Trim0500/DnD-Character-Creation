#pragma once 

/*
* \file item.h
* \brief Header file for the Item class
*
* This file puts in the forwrad declarations for the Item class and it's member fields and functions.
*/

/*
* \namespace item
* \brief namespace to encapsulate character items
*/
namespace item {
	/*
	* \enum Itemtype
	* \brief Enum for the character item types
	* 
	* Enum in the item namespace that represents the various types of items that can exist for a character to wear.
	* Each have a set amount of enchantment types they can imbue.
	*/
	enum ItemType {
		Hemlet = 1,
		Armor,
		Shield,
		Ring,
		Belt,
		Boots,
		Weapon
	};

	/*
	* \enum CharacterStats
	* \brief Enum for the character stats
	*
	* Enum in the item namespace that represents the possible stats that an item can increase when worn by a character.
	*/
	enum CharacterStats {
		Strength = 1,
		Dexterity,
		Constitution,
		Intelligence,
		Wisdom,
		Charisma,
		ArmorClass,
		AttackBonus,
		DamageBonus
	};

	/*
	* \class Item
	* \brief Class for the character items
	*
	* Class that abstracts the Items available to a character that are put into a container or worn.
	*/
	class Item {
		public:
			/*
			* \fn Item
			* \brief No-args constructor for Item
			*
			* No-args constructor that will randomly generate an item in terms of enchantment count, item type and enchantment type.
			* Implemented in item.cpp.
			*/
			Item();
			/*
			* \fn Item
			* \brief Overloaded constructor for Item
			*
			* Custom constructor that will take in specified arguments to make an instance of the Item class.
			* Note that enchantment bonus ranges from 1-5, item type ranges from 1-7 and enchantment type ranges from 1-9.
			* Implemented by item.cpp.
			*
			* @param _enchantmentBonus The reference to a constant integer representing the chosen enchantment bonus value. (1-5)
			* @param _itemType The reference to a constant integer representing the chosen item type. (1-7)
			* @param _enchantmentType The reference to a constant integer representing the chosen enchantment type value. (1-9)
			*/
			Item(const int&, const int&, const int&);
			int GetEnchantmentBonus() { return enchantmentBonus; };
			CharacterStats GetEnchantmentType() { return enchantmentType; };
		private:
			/* 
			* A variable
			*/
			int enchantmentBonus;
			/*
			* A variable
			*/
			ItemType itemType;
			/*
			* A variable
			*/
			CharacterStats enchantmentType;
	};
}
