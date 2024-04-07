/*!
* \file testitemcontainer.h
* \brief Test file for ItemContainer
*/

#pragma once

#include <iostream>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>

#include "..\Item\itemcontainer.h"

// using namespace std;
using namespace CppUnit;
using namespace itemcontainer;

/*!
* \class TestItemContainer
* \brief Test Class to run unit tests for ItemContainer
*/
class TestItemContainer : public TestFixture {
	CPPUNIT_TEST_SUITE(TestItemContainer);
	CPPUNIT_TEST(TestCustomConstructor);
	CPPUNIT_TEST(TestSetWeightCapacity);
	CPPUNIT_TEST(TestAddNewItem);
	CPPUNIT_TEST(TestRemoveItems);
	CPPUNIT_TEST(TestGetItemWeightTotal);
	CPPUNIT_TEST(TestGetItemByName);
	CPPUNIT_TEST(TestGetItemByItemType);
	CPPUNIT_TEST(TestGetAllItems);
	CPPUNIT_TEST(TestGetItemsByBonus);
	CPPUNIT_TEST(TestGetItemsByType);
	CPPUNIT_TEST(TestGetItemsByStat);
	CPPUNIT_TEST_SUITE_END();

	public:
		/*!
		* \fn setUp
		* \brief Function that creates three ItemContainer objects before running a test
		*/
		void setUp(void);
		/*!
		* \fn tearDown
		* \brief Function that deallocates the objects after a test
		*/
		void tearDown(void);
	protected:
		/*!
		* \fn TestCustomConstructor
		* \brief Function that tests the custom constructor overload for name and container type correctness
		*/
		void TestCustomConstructor(void);
		/*!
		* \fn TestSetWeightCapacity
		* \brief Function that tests the alteration to a container's weight capacity specified by character strength
		*/
		void TestSetWeightCapacity(void);
		/*!
		* \fn TestAddNewItem
		* \brief Function that tests adding in a new item to the list and ensuring the capacity is respected
		*/
		void TestAddNewItem(void);
		/*!
		* \fn TestRemoveItems
		* \brief Function that tests removing items ensuring the expected list is generated
		*/
		void TestRemoveItems(void);
		/*!
		* \fn TestGetItemWeightTotal
		* \brief Function that tests summing up the weights of the items in a container to ensure they don't fall outside the boundaries
		*/
		void TestGetItemWeightTotal(void);
		/*!
		* \fn TestGetItemByName
		* \brief Function that tests finding an item by name in the list of items (Worn Items)
		*/
		void TestGetItemByName(void);
		/*!
		* \fn TestGetItemByItemType
		* \brief Function that tests finding an item by item tyoe in the list of items (Worn Items)
		*/
		void TestGetItemByItemType(void);
		/*!
		* \fn TestGetAllItems
		* \brief Function that tests getting all the items in the list and verifying that the count is correct
		*/
		void TestGetAllItems(void);
		/*!
		* \fn TestGetItemsByBonus
		* \brief Function that tests getting all the items in the list that match the bonus criteria
		*/
		void TestGetItemsByBonus(void);
		/*!
		* \fn TestGetItemsByType
		* \brief Function that tests getting all the items in the list that match the item type
		*/
		void TestGetItemsByType(void);
		/*!
		* \fn TestGetItemsByStat
		* \brief Function that tests getting all the items in the list that match the character stat
		*/
		void TestGetItemsByStat(void);
	private:
		/*!
		* \var backpackObject
		* \brief Varaible that represents a pointer to a backpack with random items included in it's list
		*/
		ItemContainer* backpackObject;
		/*!
		* \var wornItemsObject
		* \brief Varaible that represents a pointer to a worn items container with specific items added to it's list
		*/
		ItemContainer* wornItemsObject;
		/*!
		* \var chestObject
		* \brief Varaible that represents a pointer to a chest with random items included in it's list
		*/
		ItemContainer* chestObject;
		/*!
		* \var inventoryObject
		* \brief Varaible that represents a pointer to a character's inventory
		*/
		ItemContainer* inventoryObject;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestItemContainer);
