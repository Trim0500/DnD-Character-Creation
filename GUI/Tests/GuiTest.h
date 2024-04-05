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

#include "../MainMenu.h"

// using namespace std;
using namespace CppUnit;

class TestGUI : public TestFixture {
	CPPUNIT_TEST_SUITE(TestGUI);
	CPPUNIT_TEST(TestCampaignSave);
	CPPUNIT_TEST(TestCampaignOpen);
	CPPUNIT_TEST(TestCampaignSaveAs);
	//CPPUNIT_TEST(TestImportItems);
	//CPPUNIT_TEST(TestImportItemsContainer);
	//CPPUNIT_TEST(TestImportMaps);
	//CPPUNIT_TEST(TestImportCharacter);
	//CPPUNIT_TEST();
	CPPUNIT_TEST_SUITE_END();

public:
	/*!
	* \fn setUp
	* \brief
	*/
	void setUp(void);
	/*!
	* \fn tearDown
	* \brief
	*/
	void tearDown(void) {};

protected:
	void TestCampaignSave(void);
	void TestCampaignOpen(void);
	void TestCampaignSaveAs(void);
	//void TestImportItems(void);
	//void TestImportItemsContainer(void);
	//void TestImportMaps(void);
	//void TestImportCharacter(void);
	// void TestFullRoll(void);
	// void TestAllDice(void);
private:
	CampaignEditor::MainMenu* main_menu;

};

CPPUNIT_TEST_SUITE_REGISTRATION(TestGUI);