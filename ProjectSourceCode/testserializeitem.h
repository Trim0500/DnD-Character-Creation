/*!
* \file testserializeitem.h
* \brief Test file for Item serialization
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

#include "serializeItem.h"

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
		void TestLoadItems(void);
	private:
		vector<int> containerIDOneVector;
		vector<int> containerIDTwoVector;
		vector<int> containerIDVector;
		vector<int> invalidContainerIDVector;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestSerializeItem);
