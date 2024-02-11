/*
* \file testitemcontainer.cpp
* \brief Test implementation for Item
*/

#include <iostream>
#include <vector>

#include "testitemcontainer.h"

#define BACKPACK_ITEM_SIZE 10
#define CHEST_ITEM_SIZE 20

using namespace std;

void TestItemContainer::setUp(void)
{
	backpackObject = new ItemContainer("testBackpack", Backpack);

	for (int i = 0; i < BACKPACK_ITEM_SIZE; i++)
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

	for (int i = 0; i < CHEST_ITEM_SIZE; i++)
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

void TestItemContainer::TestGetAllItems(void) {
	vector<Item> backpackItems = backpackObject->GetAllItems();
	CPPUNIT_ASSERT(backpackItems.size() == BACKPACK_ITEM_SIZE);
	
	vector<Item> wornItems = wornItemsObject->GetAllItems();
	CPPUNIT_ASSERT(wornItems.size() == 7);
	
	vector<Item> chestItems = chestObject->GetAllItems();
	CPPUNIT_ASSERT(chestItems.size() == CHEST_ITEM_SIZE);
}
