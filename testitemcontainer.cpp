/*
* \file testitemcontainer.cpp
* \brief Test implementation for Item
*/

#include <iostream>
#include <vector>

#include "testitemcontainer.h"

using namespace std;

void TestItemContainer::setUp(void)
{
	backpackObject = new ItemContainer("testBackpack", Backpack);

	for (int i = 0; i < 10; i++)
	{
		Item* newItem = new Item();
		backpackObject->AddNewItem(*newItem);
	}

	wornItemsObject = new ItemContainer("testWornItems", WornItems);

	Item* helmetObject = new Item("testHelmet", 2, Helmet, Intelligence);
	Item* armorObject = new Item("testArmor", 3, Armor, ArmorClass);
	Item* shieldObject = new Item("testShield", 2, Shield, ArmorClass);
	Item* ringObject = new Item("testRing", 1, Ring, Wisdom);
	Item* beltObject = new Item("testBelt", 1, Belt, Strength);
	Item* bootsObject = new Item("testBoots", 2, Boots, Dexterity);
	Item* weaponObject = new Item("testWeapon", 2, Weapon, AttackBonus);

	wornItemsObject->AddNewItem(*helmetObject);
	wornItemsObject->AddNewItem(*armorObject);
	wornItemsObject->AddNewItem(*shieldObject);
	wornItemsObject->AddNewItem(*ringObject);
	wornItemsObject->AddNewItem(*beltObject);
	wornItemsObject->AddNewItem(*bootsObject);
	wornItemsObject->AddNewItem(*weaponObject);

	chestObject = new ItemContainer("testChest", TreasureChest);

	for (int i = 0; i < 20; i++)
	{
		Item* newItem = new Item();
		chestObject->AddNewItem(*newItem);
	}
}

void TestItemContainer::tearDown(void)
{
	backpackObject->GetAllItems().clear();

	delete backpackObject;

	wornItemsObject->GetAllItems().clear();

	delete wornItemsObject;

	chestObject->GetAllItems().clear();

	delete chestObject;
}

void TestItemContainer::TestCustomConstructor(void) {
	CPPUNIT_ASSERT(backpackObject->GetItemName() == "testBackpack");
	CPPUNIT_ASSERT(backpackObject->GetItemType() == Backpack);

	CPPUNIT_ASSERT(wornItemsObject->GetItemName() == "testWornItems");
	CPPUNIT_ASSERT(wornItemsObject->GetItemType() == WornItems);

	CPPUNIT_ASSERT(chestObject->GetItemName() == "testChest");
	CPPUNIT_ASSERT(chestObject->GetItemType() == TreasureChest);
}
