/*!
* \file item.cpp
* \brief Implementation file for the Item class
*
* This file puts in the function implementations for the Item class
*/

#include <iostream>
#include <random>
#include <string>
#include <sstream>

#include "item.h"

using namespace std;

namespace {
	/*!
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

	/*!
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
		uniform_int_distribution<int> distrib(0, (sizeof(*allowedTypesArray) / sizeof(item::CharacterStats)) - 1);
		int indexChosen = distrib(gen);

		return allowedTypesArray[indexChosen];
	}
}

namespace item {
	Item::Item() {
		nextItemId = nextItemId + 1;
		itemId = nextItemId;
		enchantmentBonus = GenerateRandomInt(1, 5);
		itemType = (ItemType)GenerateRandomInt(Helmet, Weapon);
		switch (itemType) {
			case 1:
			{
				CharacterStats helmetEnchantmentTypes[3] = { Intelligence, Wisdom, ArmorClass };
				enchantmentType = PickEnchantmentType(helmetEnchantmentTypes);
				weight = enchantmentType  == 6 ? GenerateRandomInt(8, 13) : 5;
			}
				break;
			case 2:
			case 3:
			{
				enchantmentType = ArmorClass;
				weight = itemType == 2 ? enchantmentBonus >= 3 ? GenerateRandomInt(40, 65) : GenerateRandomInt(12, 20) : GenerateRandomInt(8, 13);
			}
				break;
			case 4:
			{
				CharacterStats ringEnchantmentTypes[5] = { ArmorClass, Strength, Constitution, Wisdom, Charisma };
				enchantmentType = PickEnchantmentType(ringEnchantmentTypes);
				weight = 0.5;
			}
				break;
			case 5:
			{
				CharacterStats beltEnchantmentTypes[2] = { Constitution, Strength };
				enchantmentType = PickEnchantmentType(beltEnchantmentTypes);
				weight = 4.5;
			}
				break;
			case 6:
			{
				CharacterStats bootsEnchantmentTypes[2] = { ArmorClass, Dexterity };
				enchantmentType = PickEnchantmentType(bootsEnchantmentTypes);
				weight = enchantmentType == 6 ? GenerateRandomInt(8, 13) : 5;
			}
				break;
			case 7:
			{
				CharacterStats weaponEnchantmentTypes[2] = { AttackBonus, DamageBonus };
				enchantmentType = PickEnchantmentType(weaponEnchantmentTypes);
				weight = enchantmentBonus >= 3 ? GenerateRandomInt(5, 18) : GenerateRandomInt(2, 4);
			}
				break;
			default:
			{
				enchantmentType = (CharacterStats)1;
				weight = 3;
			}
				break;
		}

		ostringstream name;
		name << itemTypeStrings[itemType - 1] << " +" << to_string(enchantmentBonus) << " (" << statStrings[enchantmentType] << ")";
		itemName = name.str();
	}

	Item::Item(const string& _itemName, const int& _enchantmentBonus, const int& _itemType, const int& _enchantmentType, const float& _weight) {
		nextItemId = nextItemId + 1;
		itemId = nextItemId;
		itemName = _itemName;
		enchantmentBonus = _enchantmentBonus;
		itemType = (ItemType)_itemType;
		enchantmentType = (CharacterStats)_enchantmentType;
		weight = _weight;
	}
}