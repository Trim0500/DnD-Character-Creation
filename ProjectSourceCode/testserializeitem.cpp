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

using namespace std;
using namespace serializeItem;

void TestSerializeItem::setUp(void) {
	containerIDOneVector.push_back(1);

	containerIDTwoVector.push_back(2);

	containerIDVector.push_back(1);
	containerIDVector.push_back(2);

	invalidContainerIDVector.push_back(3);
}

void TestSerializeItem::tearDown(void) {
	
}

void TestSerializeItem::TestLoadItems(void) {
	bool exceptionThrown = false;
	
	try {
		vector<ItemRecord*> testInvalidURIVector = LoadItemsByContainerIDs(INVALID_FILE_URI, containerIDOneVector);
	}
	catch (invalid_argument exc) {
		exceptionThrown = true;
	}

	CPPUNIT_ASSERT(exceptionThrown);
	
	try {
		string currentPath = filesystem::current_path().string();

		ostringstream fullURI;
		fullURI << currentPath << LOAD_SAVED_ITEMS_URI;

		cout << "The file is attempted to be found at: " << fullURI.str() << endl;

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
		cout << "Failed to find the test file URI." << endl;
	}
}
