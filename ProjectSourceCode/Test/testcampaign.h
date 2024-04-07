/*!
* \file testcampaign.h
* \brief Header file for testing the Campaign class
* 
* \author Tristan Lafleur
*/

#pragma once

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

#include "..\Campaign\campaign.h"

using namespace CppUnit;
using namespace campaign;

/*!
* \class TestCampaign
* \brief Test Class to run unit tests for Campaign
*/
class TestCampaign : public TestFixture {
    CPPUNIT_TEST_SUITE(TestCampaign);
    CPPUNIT_TEST(TestCampaignConstructor);
    CPPUNIT_TEST(TestAddNewMap);
    CPPUNIT_TEST(TestGetMap);
    CPPUNIT_TEST(TestSaveCampaign);
    CPPUNIT_TEST(TestLoadCampaign);
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
		* \fn TestCampaignConstructor
		* \brief Function that tests the custom constructor overload for static ganeration
		*/
		void TestCampaignConstructor(void);

		/*!
		* \fn TestAddNewMap
		* \brief Function that tests GetMap member function
		*/
		void TestAddNewMap(void);

		/*!
		* \fn TestGetMap
		* \brief Function that tests GetMap member function
		*/
		void TestGetMap(void);

		/*!
		* \fn TestSaveCampaign
		* \brief Function that tests the SaveCampaign member function
		*/
		void TestSaveCampaign(void);

		/*!
		* \fn TestLoadCampaign
		* \brief Function that tests the LoadCampaign member function
		*/
		void TestLoadCampaign(void);
	private:
		/*!
		* \var customCampaignObject
		* \brief Variable that represents the pointer to a fresh campaign
		*/
		Campaign* newCampaignObject;

		/*!
		* \var customItemObject
		* \brief Pointer to a Campaign instance that represents an existing campaign
		*/
		Campaign* existingCampaignObject;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestCampaign);
