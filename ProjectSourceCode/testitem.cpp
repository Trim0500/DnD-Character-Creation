	/*!
* \file testitem.cpp
* \brief Test implementation for Item
*/

#include <iostream>
#include <string>
#include <sstream>

#include "testitem.h"

#define ARMOR_HELMET_MIN_WEIGHT 8
#define ARMOR_HELMET_MAX_WEIGHT 13
#define ARMOR_LOW_ENCHANTMENT_MIN_WEIGHT 12
#define ARMOR_LOW_ENCHANTMENT_MAX_WEIGHT 20
#define ARMOR_HIGH_ENCHANTMENT_MIN_WEIGHT 40
#define ARMOR_HIGH_ENCHANTMENT_MAX_WEIGHT 65
#define SHIELD_MIN_WEIGHT 8
#define SHIELD_MAX_WEIGHT 13
#define BOOTS_MIN_WEIGHT 8
#define BOOTS_MAX_WEIGHT 13
#define WEAPON_LOW_ENCHANTMENT_MIN_WEIGHT 2
#define WEAPON_LOW_ENCHANTMENT_MAX_WEIGHT 4
#define WEAPON_HIGH_ENCHANTMENT_MIN_WEIGHT 5
#define WEAPON_HIGH_ENCHANTMENT_MAX_WEIGHT 18

// using namespace std;

void TestItem::setUp(void)
{
	noArgsItemObject = new Item();

	customItemObject = new Item("testItem", 3, Ring, Strength, 0.5);

	//testItemCurrentId += 2;
}

void TestItem::tearDown(void)
{
	delete noArgsItemObject;

	delete customItemObject;
}

void TestItem::TestNoArgsItemConstructor(void) {
	//CPPUNIT_ASSERT(noArgsItemObject->GetItemId() == testItemCurrentId - 1);
	std::ostringstream name;
	name << itemTypeStrings[noArgsItemObject->GetItemType() - 1]
			<< " +"
			<< std::to_string(noArgsItemObject->GetEnchantmentBonus())
			<< " ("
			<< statStrings[noArgsItemObject->GetEnchantmentType()] << ")";
	CPPUNIT_ASSERT(noArgsItemObject->GetItemName() == name.str());
	CPPUNIT_ASSERT(noArgsItemObject->GetEnchantmentBonus() >= 1 && noArgsItemObject->GetEnchantmentBonus() <= 5);
	CPPUNIT_ASSERT(noArgsItemObject->GetItemType() >= Helmet && noArgsItemObject->GetItemType() <= Weapon);
	CPPUNIT_ASSERT(noArgsItemObject->GetEnchantmentType() >= Strength && noArgsItemObject->GetEnchantmentType() <= DamageBonus);
}

void TestItem::TestItemConstructor(void) {
	//CPPUNIT_ASSERT(customItemObject->GetItemId() == testItemCurrentId);
	CPPUNIT_ASSERT(customItemObject->GetItemName() == "testItem");
	CPPUNIT_ASSERT(customItemObject->GetEnchantmentBonus() == 3);
	CPPUNIT_ASSERT(customItemObject->GetItemType() == Ring);
	CPPUNIT_ASSERT(customItemObject->GetEnchantmentType() == Strength);
}

void TestItem::TestGetItemId(void) {
	//CPPUNIT_ASSERT(noArgsItemObject->GetItemId() == testItemCurrentId - 1);
	
	//CPPUNIT_ASSERT(customItemObject->GetItemId() == testItemCurrentId);
}

void TestItem::TestGetItemName(void) {
	std::ostringstream name;
	name << itemTypeStrings[noArgsItemObject->GetItemType() - 1]
		<< " +"
		<< std::to_string(noArgsItemObject->GetEnchantmentBonus())
		<< " ("
		<< statStrings[noArgsItemObject->GetEnchantmentType()] << ")";
	CPPUNIT_ASSERT(noArgsItemObject->GetItemName() == name.str());

	CPPUNIT_ASSERT(customItemObject->GetItemName() == "testItem");
}

void TestItem::TestGetEnchantmentBonus(void) {
	CPPUNIT_ASSERT(noArgsItemObject->GetEnchantmentBonus() >= 1 && noArgsItemObject->GetEnchantmentBonus() <= 5);

	CPPUNIT_ASSERT(customItemObject->GetEnchantmentBonus() == 3);
}

void TestItem::TestGetItemType(void) {
	CPPUNIT_ASSERT(noArgsItemObject->GetItemType() >= Helmet && noArgsItemObject->GetItemType() <= Weapon);

	CPPUNIT_ASSERT(customItemObject->GetItemType() == Ring);
}

void TestItem::TestGetEnchantmentType(void) {
	CPPUNIT_ASSERT(noArgsItemObject->GetEnchantmentType() >= Strength && noArgsItemObject->GetEnchantmentType() <= DamageBonus);

	CPPUNIT_ASSERT(customItemObject->GetEnchantmentType() == Strength);
}

void TestItem::TestGetItemWeight(void) {
	CPPUNIT_ASSERT(customItemObject->GetItemWeight() >= 0.5);

	int randomItemEnchantmentType = noArgsItemObject->GetEnchantmentType();

	float randomItemWeight = noArgsItemObject->GetItemWeight();

	int randomItemBonus = noArgsItemObject->GetEnchantmentBonus();

	int randomItemItemType = noArgsItemObject->GetItemType();
	switch (randomItemItemType) {
		case 1:
		{
			CPPUNIT_ASSERT(randomItemEnchantmentType == 6 ?
							randomItemWeight >= ARMOR_HELMET_MIN_WEIGHT && randomItemWeight <= ARMOR_HELMET_MAX_WEIGHT :
							randomItemWeight >= 5);
		}
			break;
		case 2:
		case 3:
		{
			CPPUNIT_ASSERT(randomItemItemType == 2 ?
							randomItemBonus >= 3 ?
								randomItemWeight >= ARMOR_HIGH_ENCHANTMENT_MIN_WEIGHT && randomItemWeight <= ARMOR_HIGH_ENCHANTMENT_MAX_WEIGHT :
								randomItemWeight >= ARMOR_LOW_ENCHANTMENT_MIN_WEIGHT && randomItemWeight <= ARMOR_LOW_ENCHANTMENT_MAX_WEIGHT :
								randomItemWeight >= SHIELD_MIN_WEIGHT && randomItemWeight <= SHIELD_MAX_WEIGHT);
		}
			break;
		case 4:
		{
			CPPUNIT_ASSERT(randomItemWeight >= 0.5);
		}
			break;
		case 5:
		{
			CPPUNIT_ASSERT(randomItemWeight >= 4.5);
		}
			break;
		case 6:
		{
			CPPUNIT_ASSERT(randomItemEnchantmentType == 6 ?
							randomItemWeight >= BOOTS_MIN_WEIGHT && randomItemWeight <= BOOTS_MAX_WEIGHT :
							randomItemWeight >= 5);
		}
			break;
		case 7:
		{
			CPPUNIT_ASSERT(randomItemBonus >= 3 ?
							randomItemWeight >= WEAPON_HIGH_ENCHANTMENT_MIN_WEIGHT && randomItemWeight <= WEAPON_HIGH_ENCHANTMENT_MAX_WEIGHT :
							randomItemWeight >= WEAPON_LOW_ENCHANTMENT_MIN_WEIGHT && randomItemWeight <= WEAPON_LOW_ENCHANTMENT_MAX_WEIGHT);
		}
			break;
		default:
		{
			CPPUNIT_ASSERT(randomItemWeight >= 3);
		}
			break;
	}
}
