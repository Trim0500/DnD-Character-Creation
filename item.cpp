#include <iostream>
#include <random>

#include "item.h"

using namespace std;

namespace {
	int GenerateRandomInt(int min, int max) {
		random_device seed;
		mt19937 gen(seed);
		uniform_int_distribution<int> distrib(1, 5);

		return distrib(gen);
	}

	item::CharacterStats PickEnchantmentType(const item::CharacterStats *allowedTypesArray) {
		random_device seed;
		mt19937 gen(seed);
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
				CharacterStats helmetEnchantmentTypes[3] = { Intelligence, Wisdom, ArmorClass };
				enchantmentType = PickEnchantmentType(helmetEnchantmentTypes);

				break;
			case 2:
			case 3:
				enchantmentType = ArmorClass;

				break;
			case 4:
				CharacterStats ringEnchantmentTypes[5] = { ArmorClass, Strength, Constitution, Wisdom, Charisma };
				enchantmentType = PickEnchantmentType(ringEnchantmentTypes);

				break;
			case 5:
				CharacterStats beltEnchantmentTypes[2] = { Constitution, Strength };
				enchantmentType = PickEnchantmentType(beltEnchantmentTypes);

				break;
			case 6:
				CharacterStats bootsEnchantmentTypes[2] = { ArmorClass, Dexterity };
				enchantmentType = PickEnchantmentType(bootsEnchantmentTypes);

				break;
			case 7:
				CharacterStats weaponEnchantmentTypes[2] = { AttackBonus, DamageBonus };
				enchantmentType = PickEnchantmentType(weaponEnchantmentTypes);

				break;
		}
	}

	Item::Item(const int& _enchantmentBonus, const int& _itemType, const int& _enchantmentType) {
		enchantmentBonus = _enchantmentBonus;
		itemType = (ItemType)_itemType;
		enchantmentType = (CharacterStats)_enchantmentType;
	}

	int Item::GetEnchantmentBonus() {
		return enchantmentBonus;
	}

	CharacterStats Item::GetEnchantmentType() {
		return enchantmentType;
	}
}