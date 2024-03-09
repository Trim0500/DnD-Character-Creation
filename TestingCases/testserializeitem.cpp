/*!
* \file testserializeitem.cpp
* \brief Test implementation for Item serialization
*/

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <sys/stat.h>

#include "testserializeitem.h"
//#include "Character.h"

#define INVALID_FILE_URI "SomeDumbURI.csv"
#define LOAD_SAVED_ITEMS_URI "\\SavedItems\\TestLoadSavedItems.csv"
#define LOAD_SAVED_CONTAINERS_URI "\\SavedItems\\TestLoadSavedItemContainers.csv"
#define SAVE_SAVED_ITEMS_URI "\\SavedItems\\TestSaveSavedItems.csv"
#define SAVE_SAVED_CONTAINERS_URI "\\SavedItems\\TestSaveSavedItemContainers.csv"

using namespace std;
using namespace serializeItem;

void TestSerializeItem::setUp(void) {
	
}

void TestSerializeItem::tearDown(void) {
	
}

void TestSerializeItem::TestLoadItems(void) {
	ostringstream fileNotFoundMessage;
	fileNotFoundMessage << "Failed to open the file at: " << INVALID_FILE_URI;
	CPPUNIT_ASSERT_THROW_MESSAGE(fileNotFoundMessage.str(), LoadItems(INVALID_FILE_URI), invalid_argument);
	
	try {
		string currentPath = filesystem::current_path().string();

		ostringstream fullURI;
		fullURI << currentPath << LOAD_SAVED_ITEMS_URI;

		vector<Item*> testItems = LoadItems(fullURI.str());

		CPPUNIT_ASSERT_EQUAL(5, (int)testItems.size());
		
		Item* testRecord = testItems[1];
		CPPUNIT_ASSERT_EQUAL(2, testRecord->GetItemId());
		CPPUNIT_ASSERT("Some Armor" == testRecord->GetItemName());
		CPPUNIT_ASSERT_EQUAL(5, testRecord->GetEnchantmentBonus());
		CPPUNIT_ASSERT_EQUAL(Armor, testRecord->GetItemType());
		CPPUNIT_ASSERT_EQUAL(ArmorClass, testRecord->GetEnchantmentType());
		CPPUNIT_ASSERT_DOUBLES_EQUAL(65.0, testRecord->GetItemWeight(), 0.0001);
	}
	catch (invalid_argument exc) {
		cout << exc.what() << endl;
	}
}

void TestSerializeItem::TestLoadContainers(void) {
	ostringstream fileNotFoundMessage;
	fileNotFoundMessage << "Failed to open the file at: " << INVALID_FILE_URI;
	CPPUNIT_ASSERT_THROW_MESSAGE(fileNotFoundMessage.str(), LoadItemContainerRecords(INVALID_FILE_URI), invalid_argument);

	try {
		string currentPath = filesystem::current_path().string();

		ostringstream fullURI;
		fullURI << currentPath << LOAD_SAVED_CONTAINERS_URI;

		vector<ItemContainerRecord*> testContainerRecords = LoadItemContainerRecords(fullURI.str());

		CPPUNIT_ASSERT_EQUAL(3, (int)testContainerRecords.size());

		ItemContainerRecord* testRecord = testContainerRecords[0];
		CPPUNIT_ASSERT_EQUAL(1, testRecord->containerId);
		CPPUNIT_ASSERT("Some Backpack" == testRecord->itemName);
		CPPUNIT_ASSERT_EQUAL(Backpack, testRecord->itemtype);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, testRecord->weight, 0.0001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(30.0, testRecord->capacity, 0.0001);
		CPPUNIT_ASSERT_EQUAL(3, (int)testRecord->itemIDs.size());
		CPPUNIT_ASSERT_EQUAL(10, testRecord->itemIDs[0]);
		CPPUNIT_ASSERT_EQUAL(8, testRecord->itemIDs[1]);
		CPPUNIT_ASSERT_EQUAL(5, testRecord->itemIDs[2]);
	}
	catch (invalid_argument exc) {
		cout << exc.what() << endl;
	}
}

void TestSerializeItem::TestSaveItems(void) {
	Item* backpackShieldItem = new Item("testBackpackShield", 4, Shield, ArmorClass, 12);
	Item* backpackBootsItem = new Item("testBackpackBoots", 4, Boots, Dexterity, 5);

	Item* helmetObject = new Item("testHelmet", 2, Helmet, Intelligence, 5);
	Item* armorObject = new Item("testArmor", 3, Armor, ArmorClass, 45);

	vector<Item*> testItemVector;
	testItemVector.push_back(backpackShieldItem);
	testItemVector.push_back(backpackBootsItem);
	testItemVector.push_back(helmetObject);
	testItemVector.push_back(armorObject);

	string currentPath = filesystem::current_path().string();

	ostringstream fullURI;
	fullURI << currentPath << SAVE_SAVED_ITEMS_URI;

	CPPUNIT_ASSERT_NO_THROW(SaveItems(fullURI.str(), testItemVector));

	struct stat buffer;
	CPPUNIT_ASSERT(stat(fullURI.str().c_str(), &buffer) == 0);
}

void TestSerializeItem::TestSaveContainers(void) {
	ItemContainer* testBackpackObject = new ItemContainer("Some Backpack", Backpack, 30.0);

	Item* backpackShieldItem = new Item("testBackpackShield", 4, Shield, ArmorClass, 12);
	Item* backpackBootsItem = new Item("testBackpackBoots", 4, Boots, Dexterity, 5);
	Item* helmetObject = new Item("testHelmet", 2, Helmet, Intelligence, 5);

	testBackpackObject->AddNewItem(backpackShieldItem);
	testBackpackObject->AddNewItem(backpackBootsItem);
	testBackpackObject->AddNewItem(helmetObject);

	vector<ItemContainer*> testContainerObject;
	testContainerObject.push_back(testBackpackObject);

	string currentPath = filesystem::current_path().string();

	ostringstream fullURI;
	fullURI << currentPath << SAVE_SAVED_CONTAINERS_URI;

	CPPUNIT_ASSERT_NO_THROW(SaveItemContainers(fullURI.str(), testContainerObject));

	struct stat buffer;
	CPPUNIT_ASSERT(stat(fullURI.str().c_str(), &buffer) == 0);
}
