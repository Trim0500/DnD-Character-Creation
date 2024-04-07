
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

class TestCharacter : public CppUnit::TestFixture
{
		CPPUNIT_TEST_SUITE(TestCharacter);
		CPPUNIT_TEST(TestNoArgsCharacterConstructor);
		CPPUNIT_TEST(TestCharacterConstructor);
		CPPUNIT_TEST(TestGetCharacterID);
		CPPUNIT_TEST(TestGetCharacterName);
		CPPUNIT_TEST(TestSumLevels);
		CPPUNIT_TEST(TestClasses);
		CPPUNIT_TEST(TestEquipItem);
		CPPUNIT_TEST(TestEquipItemDecorator);
		CPPUNIT_TEST(TestUnequipItem);
		CPPUNIT_TEST(TestUnequipItemDecorator);
		CPPUNIT_TEST(TestMaxHitPoints);
		CPPUNIT_TEST(TestHitPoints);
		CPPUNIT_TEST(TestAbilityScore);
		CPPUNIT_TEST(TestArmourClass);
		CPPUNIT_TEST(TestAttackBonus);
		CPPUNIT_TEST(TestProficiencyBonus);
		CPPUNIT_TEST(TestDamageBonus);
		CPPUNIT_TEST(TestActionStrategy);
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
		
		void TestEquipItemDecorator(void);

		void TestUnequipItem(void);
		
		void TestUnequipItemDecorator(void);

		void TestMaxHitPoints(void);

		void TestHitPoints(void);

		void TestAbilityScore(void);

		void TestArmourClass(void);
		
		void TestAttackBonus(void);

		void TestProficiencyBonus(void);

		void TestDamageBonus(void);

		void TestActionStrategy(void);
	private:
		Character::Character* noArgsCharacterObject;

		Character::Character* customCharacterObject;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestCharacter);