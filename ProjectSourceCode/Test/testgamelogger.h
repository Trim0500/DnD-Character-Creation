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

#include "../Game/gamelogger.h"
#include "../Game/game.h"

using namespace CppUnit;
using namespace gamelogger;
using namespace game;

class TestGameLogger : public TestFixture {
    CPPUNIT_TEST_SUITE(TestGameLogger);
    CPPUNIT_TEST(TestNoArgsLoggerConstructor);
    CPPUNIT_TEST(TestLoggerConstructor);
    CPPUNIT_TEST(TestUpdate);
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
		* \fn TestNoArgsLoggerConstructor
		* \brief Function that tests the no args constructor overload for static ganeration
		*/
		void TestNoArgsLoggerConstructor(void);

        /*!
		* \fn TestLoggerConstructor
		* \brief Function that tests the custom constructor overload for static ganeration
		*/
		void TestLoggerConstructor(void);

        /*!
		* \fn TestLoggerConstructor
		* \brief Function that tests the update overriden function to ensure logs are entered
		*/
		void TestUpdate(void);
    private:
        GameLogger* noArgsLoggerObject;
        
        GameLogger* customLoggerObject;

        Game* gameObject;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestGameLogger);
