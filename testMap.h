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

#include "Map.h"

class TestMap : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(TestMap);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST(testGetRows);
	CPPUNIT_TEST(testGetCols);
	CPPUNIT_TEST(testGetEnd_Cell);
	CPPUNIT_TEST(testGetGrid);
	CPPUNIT_TEST(testGridCreation);
	CPPUNIT_TEST(testChangeCellType);
	CPPUNIT_TEST(testConvertToCellType);
	//CPPUNIT_TEST(testPath);
	CPPUNIT_TEST(testValidCell);
	//CPPUNIT_TEST();
	//CPPUNIT_TEST();
	//CPPUNIT_TEST();

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp(void);
	void tearDown(void);
protected:
	void testConstructor(void);
	void testGetRows(void);
	void testGetCols(void);
	void testGetEnd_Cell(void);
	void testGetGrid(void);
	void testGridCreation(void);
	void testChangeCellType(void);
	void testConvertToCellType(void);
	void testPath(void);
	void testValidCell(void);
private:
	Map::Map* mapWithParams;
	Map::Map* mapNoPath;
	Map::Map* mapLongPath;
	Map::Map* mapEmpty;
	vector<vector<bool>> visitedEmpty;
	vector<vector<bool>> visited;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestMap);