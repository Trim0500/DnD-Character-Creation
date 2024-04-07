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

#include "..\Character\Character.h"
#include "..\Serialize\SerializeCharacter.h"

class TestSerializeCharacter : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestSerializeCharacter);
	CPPUNIT_TEST(TestSaveCharacter);
	CPPUNIT_TEST(TestFindCharacterFile);
	CPPUNIT_TEST(TestLoadCharacter);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp(void);
	void tearDown(void);
protected:
	void TestSaveCharacter(void);
	void TestFindCharacterFile(void);
	void TestLoadCharacter(void);

private:
	Character::Character* characterObject;
	std::string filename;

};

CPPUNIT_TEST_SUITE_REGISTRATION(TestSerializeCharacter);