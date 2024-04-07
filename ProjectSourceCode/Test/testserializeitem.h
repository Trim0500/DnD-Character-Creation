/*!
* \file testserializeitem.h
* \brief Test file for Item serialization
* 
* \author Tristan Lafleur (40245238)
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

#include "..\Serialize\serializeItem.h"

using namespace std;
using namespace CppUnit;
using namespace serializeItem;

/*!
* \class TestSerializeItem
* \brief Test Class to run unit tests for Item serialization
*/
class TestSerializeItem : public TestFixture {
	CPPUNIT_TEST_SUITE(TestSerializeItem);
	CPPUNIT_TEST(TestLoadItems);
	CPPUNIT_TEST(TestLoadContainers);
	CPPUNIT_TEST(TestSaveItems);
	CPPUNIT_TEST(TestSaveContainers);
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
		* \fn TestLoadItems
		* \brief Function that tests the LoadItems function to verify correct loading of CSV Items
		*/
		void TestLoadItems(void);

		/*!
		* \fn TestLoadContainers
		* \brief Function that tests the LoadContainers function to verify correct loading of CSV container records
		*/
		void TestLoadContainers(void);

		/*!
		* \fn TestSaveItems
		* \brief Function that tests the SaveItems function to verify correct saving of CSV items
		*/
		void TestSaveItems(void);

		/*!
		* \fn TestSaveContainers
		* \brief Function that tests the SaveContainers function to verify correct saving of CSV containers
		*/
		void TestSaveContainers(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestSerializeItem);
