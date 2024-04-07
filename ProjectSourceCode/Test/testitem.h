/*!
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

#include "..\Item\item.h"
#include "..\Character\Character.h"

using namespace CppUnit;
using namespace item;

/*!
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
	CPPUNIT_TEST(TestGetItemWeight);
	CPPUNIT_TEST(TestAbilityScoreNatural);
	CPPUNIT_TEST_SUITE_END();

	public:
		/*!
		* \fn setUp
		* \brief Function that creates two Item objects before running a test
		*/
		void setUp(void);

		/*!
		* \fn tearDown
		* \brief Function that deallocates the generated items
		*/
		void tearDown(void);
	protected:
		/*!
		* \fn TestNoArgsItemConstructor
		* \brief Function that tests the no args constructor overload for random generation
		*/
		void TestNoArgsItemConstructor(void);

		/*!
		* \fn TestItemConstructor
		* \brief Function that tests the custom constructor overload for static ganeration
		*/
		void TestItemConstructor(void);

		/*!
		* \fn TestGetItemId
		* \brief Function that tests GetItemId member function to verify the id increment is correct
		*/
		void TestGetItemId(void);
		
		/*!
		* \fn TestGetItemName
		* \brief Function that tests GetItemName member function to verify the created item's name is correct
		*/
		void TestGetItemName(void);
		
		/*!
		* \fn TestGetEnchantmentBonus
		* \brief Function that tests GetEnchantmentBonus member function to verify the created item's bonus is in the right range
		*/
		void TestGetEnchantmentBonus(void);

		/*!
		* \fn TestGetItemType
		* \brief Function that tests GetItemType member function to verify the created item's type is in the right range
		*/
		void TestGetItemType(void);

		/*!
		* \fn TestGetEnchantmentType
		* \brief Function that tests GetEnchantmentType member function to verify the created item's enchantment type is in the right range
		*/
		void TestGetEnchantmentType(void);

		/*!
		* \fn TestGetItemWeight
		* \brief Function that tests GetItemWeight member function to verify the created item's weight is in the expected range
		*/
		void TestGetItemWeight(void);

		/*!
		* \fn TestAbilityScoreNatural
		* \brief Function that tests Ability_Score_Natural overrided function to assure that the item augmentation works
		*/
		void TestAbilityScoreNatural(void);
	private:
		/*!
		* \var noArgsItemObject
		* \brief Variable that represents the pointer to a randomly generated item
		*/
		Item* noArgsItemObject;
		/*!
		* \var customItemObject
		* \brief Variable that represents the pointer to a statically generated item
		*/
		Item* customItemObject;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestItem);
