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

// using namespace std;
using std::string;

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
		std::random_device seed;
		std::mt19937 gen(seed());
		std::uniform_int_distribution<int> distrib(min, max);

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
		std::random_device seed;
		std::mt19937 gen(seed());
		std::uniform_int_distribution<int> distrib(0, (sizeof(*allowedTypesArray) / sizeof(item::CharacterStats)) - 1);
		int indexChosen = distrib(gen);

		return allowedTypesArray[indexChosen];
	}
}

namespace item {
	Item::Item() : ComponentDecorator() {
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

		std::ostringstream name;
		name << itemTypeStrings[itemType - 1] << " +" << std::to_string(enchantmentBonus) << " (" << statStrings[enchantmentType] << ")";
		itemName = name.str();
		wrappee = nullptr;
	}

	Item::Item(const std::string& _itemName,
				const int& _enchantmentBonus,
				const int& _itemType,
				const int& _enchantmentType,
				const float& _weight) : ComponentDecorator() {
		nextItemId = nextItemId + 1;
		itemId = nextItemId;
		itemName = _itemName;
		enchantmentBonus = _enchantmentBonus;
		itemType = (ItemType)_itemType;
		enchantmentType = (CharacterStats)_enchantmentType;
		weight = _weight;
		wrappee = nullptr;
	}

	Item::Item(const int& _itemId,
				const string& _itemName,
				const int& _enchantmentBonus,
				const int& _itemType,
				const int& _enchantmentType,
				const float& _weight) : ComponentDecorator() {
		itemId = _itemId;
		itemName = _itemName;
		enchantmentBonus = _enchantmentBonus;
		itemType = (ItemType)_itemType;
		enchantmentType = (CharacterStats)_enchantmentType;
		weight = _weight;
		wrappee = nullptr;
	}

	int Item::Ability_Score_Natural(int _abilityScore, int _attackTurnNumber) {
		int result = wrappee->Ability_Score_Natural(_abilityScore, _attackTurnNumber);

		if (enchantmentType == _abilityScore) {
			result += enchantmentBonus;
		}

		return result;
	}

	int Item::ModifierDecorator(int _abilityScore) {
		if (_abilityScore == 6) {
			int armorResult = Ability_Score_Natural(_abilityScore, 0) + ModifierDecorator(CharacterStats::Dexterity);

			return armorResult;
		}

		int scoreResult = Ability_Score_Natural(_abilityScore, 0);

		int modifier{ 0 };
		try {
			modifier = std::floor(((float)(scoreResult - 10) / 2));
		}
		catch (std::exception& e) {
			std::cerr << &e << std::endl;
			
			return 0;
		}

		return modifier;
	}

	std::vector<AbstractComponent*> Item::GetDecoratorList() {
		std::vector<AbstractComponent*> decoratorList = wrappee->GetDecoratorList();
		decoratorList.push_back(this);

		return decoratorList;
	}

	std::string item::Item::serialize() {
		std::string str = "i,";
		str += std::to_string(this->itemId);
		return str;
		//i,id
	}
}