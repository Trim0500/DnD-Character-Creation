/*
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

#include "itemcontainer.h"

using namespace std;
using namespace CppUnit;
using namespace itemcontainer;

/*
* \class TestItemContainer
* \brief Test Class to run unit tests for ItemContainer
*/
class TestItemContainer : public TestFixture {
	CPPUNIT_TEST_SUITE(TestItemContainer);
	CPPUNIT_TEST(TestCustomConstructor);
	CPPUNIT_TEST(TestGetAllItems);
	CPPUNIT_TEST(TestGetItemsByBonus);
	CPPUNIT_TEST(TestGetItemsByType);
	CPPUNIT_TEST(TestGetItemsByStat);
	CPPUNIT_TEST(TestAddNewItem);
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp(void);
		void tearDown(void);
	protected:
		void TestCustomConstructor(void);
		void TestGetAllItems(void);
		void TestGetItemsByBonus(void);
		void TestGetItemsByType(void);
		void TestGetItemsByStat(void);
		void TestAddNewItem(void);
	private:
		ItemContainer* backpackObject;
		ItemContainer* wornItemsObject;
		ItemContainer* chestObject;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestItemContainer);
