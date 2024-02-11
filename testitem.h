/*
* \file testitem.h
* \brief Test file for Item
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

#include "item.h"

using namespace std;
using namespace CppUnit;
using namespace item;


/*
* \class TestItem
* \brief Test Class to run unit tests for Item
*/
class TestItem : public TestFixture {
	CPPUNIT_TEST_SUITE(TestItem);
	CPPUNIT_TEST(TestNoArgsItemConstructor);
	CPPUNIT_TEST(TestItemConstructor);
	CPPUNIT_TEST(TestGetItemId);
	CPPUNIT_TEST(TestGetItemName);
	CPPUNIT_TEST(TestGetEnchantmentBonus);
	CPPUNIT_TEST(TestGetItemType);
	CPPUNIT_TEST(TestGetEnchantmentType);
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp(void);
		void tearDown(void);
	protected:
		void TestNoArgsItemConstructor(void);
		void TestItemConstructor(void);
		void TestGetItemId(void);
		void TestGetItemName(void);
		void TestGetEnchantmentBonus(void);
		void TestGetItemType(void);
		void TestGetEnchantmentType(void);
	private:
		Item* noArgsItemObject;
		Item* customItemObject;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestItem);
