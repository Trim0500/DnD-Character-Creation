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

#include "..\Dice\Dice.h"

// using namespace std;
using namespace CppUnit;

class TestDice : public TestFixture {
	CPPUNIT_TEST_SUITE(TestDice);
	CPPUNIT_TEST(TestConstructor);
	CPPUNIT_TEST(TestAddDice);
	CPPUNIT_TEST(TestInvalidQuery);
	CPPUNIT_TEST(TestStaticRoll);
	CPPUNIT_TEST(TestAdditionNoRoll);
	CPPUNIT_TEST(TestRollNoAddition);
	CPPUNIT_TEST(TestFullRoll);
	CPPUNIT_TEST(TestSubtractionNoRoll);
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
	void tearDown(void);
	/*!
	 * @brief Helper function to roll thousands of dice
	 * @param d Dice object to test
	 * @param count number of times to roll the dice
	 * @return [0] -> minimum value rolled; [1] -> maximum value rolled;
	*/

protected:
	void TestConstructor(void);
	void TestStaticRoll(void);
	void TestAddDice(void);
	void TestInvalidQuery(void);
	void TestAdditionNoRoll(void);
	void TestRollNoAddition(void);
	void TestSubtractionNoRoll(void);
	void TestFullRoll(void);
	void TestAllDice(void);
private:
	std::string easy_query;
	std::string hard_query;
	std::string invalid_query;
	std::string just_add_query;
	std::string just_subtract_query;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestDice);
int testRollMin(std::string query, int count);
int testRollMin(Dice &d, int count);
int testRollMax(std::string query, int count);
int testRollMax(Dice &d, int count);