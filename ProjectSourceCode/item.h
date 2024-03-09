/*!!
* \file item.h
* \brief Header file for the Item class
* 
* @author Tristan Lafleur (40245238)
*
* This file puts in the forward declarations for the Item class and it's member fields and functions.
* 
* The game rules involved in the design of this file follow the d20 5e DnD rules. This means that the items can range from up to
*     7 different tyoes & give out an enchantment bonus to a character stat of up to +5. The items bonus are used in conjunction
*     with character modifiers to influence the value of a dice roll to acheive a combat or non-combat situation based on armor
*     or difficulty class respectively.
* 
* The design of this header file is meant to implement the generation of items as well as being able to retrieve certain pieces
*     of information related to the item. To that end, the design of the class contains the necessary members outlined in the
*     assignment specifications as well as a name and id property for uniqueness. The no args constructor is implemented using
*     random number generation for containers like treasure chests. 
* 
* The implmenetation uses the string, sstream and random libraries for name formatting and random number generation through uniform
*     distribution. The reasoning is due to the need to be able to give descriptive names to randomly generated items and have
*     a reliable random number mechanism to be able to pick out different item types, bonuses and enchantment types upon repeat
*     uses.
*/

#pragma once 

#include <iostream>
#include <string>

using namespace std;

/*!!
* \namespace item
* \brief namespace to encapsulate character items
*/
namespace item {
	/*!
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
		TreasureChest,
		Inventory
	};

	/*!
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

	/*!
	* \class Item
	* \brief Class for the character items
	*
	* Class that abstracts the Items available to a character that are put into a container or worn.
	*/
	class Item {
		public:
			/*!
			* \var itemTypeStrings
			* \brief String array for formatting item name item type
			*/
			string itemTypeStrings[7] = { "Helmet", "Armor", "Shield", "Ring", "Belt", "Boots", "Weapon" };

			/*!
			* \var itemTypeStrings
			* \brief String array for formatting item name character stat
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

			/*!
			* \fn Item
			* \brief No-args constructor for Item
			*
			* No-args constructor that will randomly generate an item in terms of enchantment count, item type and enchantment type.
			* Implemented in item.cpp.
			*/
			Item();

			/*!
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
			* @param _weight The reference to a constant float representing the chosen weight vaule. This weight depends on the item type.
			*/
			Item(const string&, const int&, const int&, const int&, const float&);

			/*!
			* \fn Item
			* \brief Overloaded constructor for Item
			*
			* Custom constructor that will take in specified arguments to make an instance of the Item class.
			* Note that enchantment bonus ranges from 1-5, item type ranges from 1-7 and enchantment type ranges from 1-9.
			* Implemented by item.cpp.
			*
			* @param _itemId Integer that represents the retrieved item id from a csv
			* @param _itemName The reference to the name given to the item.
			* @param _enchantmentBonus The reference to a constant integer representing the chosen enchantment bonus value. (0-5)
			* @param _itemType The reference to a constant integer representing the chosen item type. (1-10)
			* @param _enchantmentType The reference to a constant integer representing the chosen enchantment type value. (0-9)
			* @param _weight The reference to a constant float representing the chosen weight vaule. This weight depends on the item type.
			*/
			Item(const int&, const string&, const int&, const int&, const int&, const float&);

			friend bool operator==(const Item& lhs, const Item& rhs) { return lhs.itemName == rhs.itemName; };

			void SetItemIDCounter(int _nextID) { nextItemId = _nextID; };

			int GetItemId() { return itemId; };

			void SetItemID(int _itemID) { itemId = _itemID; };

			string GetItemName() { return itemName; };
			
			void SetItemName(std::string _itemName) { itemName = _itemName; };

			int GetEnchantmentBonus() { return enchantmentBonus; };

			void SetEnchantmentBonus(int _bonus) { enchantmentBonus = _bonus; };

			ItemType GetItemType() { return itemType; }

			void SetItemType(ItemType _type) { itemType = _type; };

			CharacterStats GetEnchantmentType() { return enchantmentType; };

			void SetEnchantmentType(CharacterStats _type) { enchantmentType = _type; };

			float GetItemWeight() { return weight; };

			void SetItemWeight(float _weight) { weight = _weight; };
		private:
			static inline int nextItemId = 0;

			/*!
			* \var itemId
			* \brief Integer that represents the item's unique ID
			*/
			int itemId;

			/*!
			* \var itemName
			* \brief Integer that represents the item's name
			*/
			string itemName;

			/*!
			* \var enchantmentBonus
			* \brief Integer that represents the item's stat bonus
			*/
			int enchantmentBonus;

			/*!
			* \var enchantmentBonus
			* \brief Integer that represents the item's type
			*/
			ItemType itemType;

			/*!
			* \var enchantmentType
			* \brief Integer that represents the item's stat
			*/
			CharacterStats enchantmentType;

			/*!
			* \var weight
			* \brief Float that represents the weight (in lbs) of an item
			*/
			float weight;
	};
}
