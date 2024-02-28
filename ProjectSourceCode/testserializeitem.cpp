/*!
* \file testserializeitem.cpp
* \brief Test implementation for Item serialization
*/

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>

#include "testserializeitem.h"

#define INVALID_FILE_URI "SomeDumbURI.csv"
#define LOAD_SAVED_ITEMS_URI "\\SavedItems\\TestLoadSavedItems.csv"
#define LOAD_SAVED_CONTAINERS_URI "\\SavedItems\\TestLoadSavedItemContainers.csv"

using namespace std;
using namespace serializeItem;

void TestSerializeItem::setUp(void) {
	containerIDOneVector.push_back(1);

	containerIDTwoVector.push_back(2);

	containerIDVector.push_back(1);
	containerIDVector.push_back(2);

	invalidContainerIDVector.push_back(3);
	
	characterIDVector.push_back(8);

	mapCellIDVector.push_back(5);

	allIDVector.push_back(8);
	allIDVector.push_back(5);

	invalidIDVector.push_back(10);
}

void TestSerializeItem::tearDown(void) {
	
}

void TestSerializeItem::TestLoadItems(void) {
	ostringstream fileNotFoundMessage;
	fileNotFoundMessage << "Failed to open the file at: " << INVALID_FILE_URI;
	CPPUNIT_ASSERT_THROW_MESSAGE(fileNotFoundMessage.str(), LoadItemsByContainerIDs(INVALID_FILE_URI, containerIDOneVector), invalid_argument);
	
	try {
		string currentPath = filesystem::current_path().string();

		ostringstream fullURI;
		fullURI << currentPath << LOAD_SAVED_ITEMS_URI;

		vector<ItemRecord*> testContainer1ItemRecords = LoadItemsByContainerIDs(fullURI.str(), containerIDOneVector);

		CPPUNIT_ASSERT_EQUAL(3, (int)testContainer1ItemRecords.size());
		
		ItemRecord* testRecord = testContainer1ItemRecords[1];
		CPPUNIT_ASSERT_EQUAL(2, testRecord->itemId);
		CPPUNIT_ASSERT_EQUAL(1, testRecord->containerId);
		CPPUNIT_ASSERT_EQUAL(1, testRecord->containerId);
		CPPUNIT_ASSERT("Some Armor" == testRecord->itemName);
		CPPUNIT_ASSERT_EQUAL(5, testRecord->enchantmentBonus);
		CPPUNIT_ASSERT_EQUAL(Armor, testRecord->itemtype);
		CPPUNIT_ASSERT_EQUAL(ArmorClass, testRecord->enchantmentType);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(65.0, testRecord->weight, 0.0001);
	}
	catch (invalid_argument exc) {
		cout << exc.what() << endl;
	}
}

void TestSerializeItem::TestLoadContainers(void) {
	ostringstream fileNotFoundMessage;
	fileNotFoundMessage << "Failed to open the file at: " << INVALID_FILE_URI;
	CPPUNIT_ASSERT_THROW_MESSAGE(fileNotFoundMessage.str(), LoadItemContainersByIDs(INVALID_FILE_URI, characterIDVector), invalid_argument);

	try {
		string currentPath = filesystem::current_path().string();

		ostringstream fullURI;
		fullURI << currentPath << LOAD_SAVED_CONTAINERS_URI;

		vector<ItemContainerRecord*> testContainer1ItemRecords = LoadItemContainersByIDs(fullURI.str(), characterIDVector);

		CPPUNIT_ASSERT_EQUAL(2, (int)testContainer1ItemRecords.size());

		ItemContainerRecord* testRecord = testContainer1ItemRecords[0];
		CPPUNIT_ASSERT_EQUAL(1, testRecord->containerId);
		CPPUNIT_ASSERT_EQUAL(8, testRecord->characterId);
		CPPUNIT_ASSERT_EQUAL(0, testRecord->mapCellId);
		CPPUNIT_ASSERT("Some Backpack" == testRecord->itemName);
		CPPUNIT_ASSERT_EQUAL(0, testRecord->enchantmentBonus);
		CPPUNIT_ASSERT_EQUAL(Backpack, testRecord->itemtype);
		CPPUNIT_ASSERT_EQUAL(NA, testRecord->enchantmentType);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, testRecord->weight, 0.0001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(30.0, testRecord->capacity, 0.0001);
	}
	catch (invalid_argument exc) {
		cout << exc.what() << endl;
	}
}
