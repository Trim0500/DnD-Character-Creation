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

void TestItem::TestAbilityScoreNatural(void) {
	std::vector<int> abilityScores = { 5, 5, 5, 5, 5, 5 };
	Character::Character* testCharacter = new Character::Character("Anristt",
																	Character::Character_Class::Ranger,
																	abilityScores,
																	true);

	Item* helmetObject = new Item("testHelmet", 2, Helmet, Intelligence, 5);
	Item* shieldObject = new Item("testShield", 2, Shield, ArmorClass, 10);
	Item* ringObject = new Item("testRing", 1, Ring, Wisdom, 0.5);
	Item* beltObject = new Item("testBelt", 1, Belt, Strength, 4.5);
	Item* bootsObject = new Item("testBoots", 2, Boots, Dexterity, 5);
	Item* weaponObject = new Item("testWeapon", 2, Weapon, AttackBonus, 3);

	testCharacter->Inventory().AddNewItem(helmetObject);
	testCharacter->Inventory().AddNewItem(shieldObject);
	testCharacter->Inventory().AddNewItem(ringObject);
	testCharacter->Inventory().AddNewItem(beltObject);
	testCharacter->Inventory().AddNewItem(bootsObject);
	testCharacter->Inventory().AddNewItem(weaponObject);

	testCharacter->Equip_Item_Decorator(helmetObject);
	testCharacter->Equip_Item_Decorator(shieldObject);
	testCharacter->Equip_Item_Decorator(ringObject);
	testCharacter->Equip_Item_Decorator(beltObject);
	testCharacter->Equip_Item_Decorator(bootsObject);
	testCharacter->Equip_Item_Decorator(weaponObject);

	AbstractComponent* currentWornItems = testCharacter->GetWornItems();
	CPPUNIT_ASSERT_EQUAL(6, currentWornItems->Ability_Score_Natural(0, 0));
	CPPUNIT_ASSERT_EQUAL(7, currentWornItems->Ability_Score_Natural(1, 0));
	CPPUNIT_ASSERT_EQUAL(5, currentWornItems->Ability_Score_Natural(2, 0));
	CPPUNIT_ASSERT_EQUAL(7, currentWornItems->Ability_Score_Natural(3, 0));
	CPPUNIT_ASSERT_EQUAL(6, currentWornItems->Ability_Score_Natural(4, 0));
	CPPUNIT_ASSERT_EQUAL(5, currentWornItems->Ability_Score_Natural(5, 0));
	CPPUNIT_ASSERT_EQUAL(19, (currentWornItems->Ability_Score_Natural(6, 0) + currentWornItems->Ability_Score_Natural(1, 0)));
	CPPUNIT_ASSERT_EQUAL(3, currentWornItems->Ability_Score_Natural(7, 1));
	CPPUNIT_ASSERT_EQUAL(-7, currentWornItems->Ability_Score_Natural(7, 3));
	CPPUNIT_ASSERT_EQUAL(6, (currentWornItems->Ability_Score_Natural(8, 0) + currentWornItems->Ability_Score_Natural(0, 0)));

	delete testCharacter;

	delete helmetObject;
	delete shieldObject;
	delete ringObject;
	delete beltObject;
	delete bootsObject;
	delete weaponObject;
}
