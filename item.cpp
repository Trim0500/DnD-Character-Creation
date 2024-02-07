/*
* \file item.cpp
* \brief Implementation file for the Item class
*
* This file puts in the function implementations for the Item class
*/

#include <iostream>
#include <random>

#include "item.h"

using namespace std;

namespace {
	/*
	* \fn GenerateRandomInt
	* \brief RNG index helper function for Item
	*
	* Helper function to the Item class to generate an int corresponding to the index of an enchantment bonus or item type.
	*
	* @param min The minimum index in the range to pick from
	* @param max The maximum index in the range to pick from
	*
	* @returns Integer that represents the index that was randomly generated from the specified range
	*/
	int GenerateRandomInt(int min, int max) {
		random_device seed;
		mt19937 gen(seed());
		uniform_int_distribution<int> distrib(min, max);

		return distrib(gen);
	}

	/*
	* \fn PickEnchantmentType
	* \brief RNG index helper function for Item's item types 
	*
	* Helper function to the Item class to generate an int corresponding to the index of an enchantment type.
	* Uses the array to specify the index range.
	*
	* @param allowedTypesArray An address pointing to a constant array to extract a type via a randomly generated index
	*
	* @returns Enum index that represents the assigned enchantment type for the item.
	*/
	item::CharacterStats PickEnchantmentType(const item::CharacterStats *allowedTypesArray) {
		random_device seed;
		mt19937 gen(seed());
		uniform_int_distribution<int> distrib(0, sizeof(allowedTypesArray) - 1);
		int indexChosen = distrib(gen);

		return allowedTypesArray[indexChosen];
	}
}

namespace item {
	Item::Item() {
		enchantmentBonus = GenerateRandomInt(1, 5);
		itemType = (ItemType)GenerateRandomInt(1, 7);
		switch (itemType) {
			case 1:
			{
				CharacterStats helmetEnchantmentTypes[3] = { Intelligence, Wisdom, ArmorClass };
				enchantmentType = PickEnchantmentType(helmetEnchantmentTypes);
			}
				break;
			case 2:
			case 3:
			{
				enchantmentType = ArmorClass;
			}
				break;
			case 4:
			{
				CharacterStats ringEnchantmentTypes[5] = { ArmorClass, Strength, Constitution, Wisdom, Charisma };
				enchantmentType = PickEnchantmentType(ringEnchantmentTypes);
			}
				break;
			case 5:
			{
				CharacterStats beltEnchantmentTypes[2] = { Constitution, Strength };
				enchantmentType = PickEnchantmentType(beltEnchantmentTypes);
			}
				break;
			case 6:
			{
				CharacterStats bootsEnchantmentTypes[2] = { ArmorClass, Dexterity };
				enchantmentType = PickEnchantmentType(bootsEnchantmentTypes);
			}
				break;
			case 7:
			{
				CharacterStats weaponEnchantmentTypes[2] = { AttackBonus, DamageBonus };
				enchantmentType = PickEnchantmentType(weaponEnchantmentTypes);
			}
				break;
		}
	}

	Item::Item(const string& _itemName, const int& _enchantmentBonus, const int& _itemType, const int& _enchantmentType) {
		itemName = _itemName;
		enchantmentBonus = _enchantmentBonus;
		itemType = (ItemType)_itemType;
		enchantmentType = (CharacterStats)_enchantmentType;
	}
}