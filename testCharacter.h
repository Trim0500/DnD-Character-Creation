
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

#include "Character.h"

class TestCharacter : public CppUnit::TestFixture
{
		CPPUNIT_TEST_SUITE(TestCharacter);

		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp(void);
		void tearDown(void);
	protected:
		void TestNoArgsCharacterConstructor(void);
		void TestCharacterConstructor(void);
		void TestGetCharacterID(void);
		void TestGetCharacterName(void);
		void TestSumLevels(void);
		void TestLevels(void);
		void TestClasses(void);
		void TestEquipItem(void);
		void TestUnequipItem(void);
		void TestMaxHitPoints(void);
		void TestHitPoints(void);
		void TestAbilityScore(void);
		void TestArmourClass(void);
		void TestAttackBonus(void);
		void TestProficiencyBonus(void);
		void TestDamageBonus(void);

	private:
		Character::Character* noArgsCharacterObject;
		Character::Character* customCharacterObject;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestCharacter);