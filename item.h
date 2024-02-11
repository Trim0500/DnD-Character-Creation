/*
* \file item.h
* \brief Header file for the Item class
*
* This file puts in the forwrad declarations for the Item class and it's member fields and functions.
*/

#pragma once 

#include <iostream>
#include <string>

using namespace std;

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
		Helmet = 1,
		Armor,
		Shield,
		Ring,
		Belt,
		Boots,
		Weapon,
		Backpack,
		WornItems,
		TreasureChest
	};

	/*
	* \enum CharacterStats
	* \brief Enum for the character stats
	*
	* Enum in the item namespace that represents the possible stats that an item can increase when worn by a character.
	*/
	enum CharacterStats {
		Strength = 0,
		Dexterity,
		Constitution,
		Intelligence,
		Wisdom,
		Charisma,
		ArmorClass,
		AttackBonus,
		DamageBonus,
		NA
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
			* A variable
			*/
			string itemTypeStrings[7] = { "Helmet", "Armor", "Shield", "Ring", "Belt", "Boots", "Weapon" };
			/*
			* A variable
			*/
			string statStrings[9] = { "Strength",
										"Dexterity",
										"Constitution",
										"Intelligence",
										"Wisdom",
										"Charisma",
										"Armor Class",
										"Attack Bonus",
										"Damage Bonus" };
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
			* @param _itemName The reference to the name given to the item.
			* @param _enchantmentBonus The reference to a constant integer representing the chosen enchantment bonus value. (0-5)
			* @param _itemType The reference to a constant integer representing the chosen item type. (1-10)
			* @param _enchantmentType The reference to a constant integer representing the chosen enchantment type value. (0-9)
			*/
			Item(const string&, const int&, const int&, const int&);
			friend bool operator==(const Item& lhs, const Item& rhs) { return lhs.itemName == rhs.itemName; };
			int GetItemId() { return itemId; };
			string GetItemName() { return itemName; };
			int GetEnchantmentBonus() { return enchantmentBonus; };
			ItemType GetItemType() { return itemType; }
			CharacterStats GetEnchantmentType() { return enchantmentType; };
		private:
			static inline int nextItemId = 0;
			/*
			* A variable
			*/
			int itemId;
			/*
			* A variable
			*/
			string itemName;
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
