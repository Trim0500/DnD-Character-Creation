/*!
* \file testMap.h
* \brief Header file for the TestMap class
*
* @author Michelle Polonsky
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

#include "Map.h"

/*!
* \class TestMap
* \brief Test Class to run unit tests for Map
*/
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
	CPPUNIT_TEST(testPath);
	CPPUNIT_TEST(testValidCell);
	CPPUNIT_TEST_SUITE_END();

public:
	/*!
	* \fn setUp
	* \brief function to set up all map variants and helper variables to be tested
	*/
	void setUp(void);
	/*!
	* \fn tearDown
	* \brief function to dealocate all generated maps
	*/
	void tearDown(void);
protected:
	/*!
	* \fn testConstructor
	* \brief function to test the Map constructor
	*/
	void testConstructor(void);
	/*!
	* \fn testGetRows
	* \brief function to test the rows getter: getRows()
	*/
	void testGetRows(void);
	/*!
	* \fn testGetCols
	* \brief function to test the columns getter: getCols()
	*/
	void testGetCols(void);
	/*!
	* \fn testGetEnd_Cell
	* \brief function to test the end_cell getter: End_Cell()
	*/
	void testGetEnd_Cell(void);
	/*!
	* \fn testGetGrid
	* \brief function to test the grid getter: Grid()
	*/
	void testGetGrid(void);
	/*!
	* \fn testGridCreation
	* \brief function to test that the map grid is created of correct height and width 
	*/
	void testGridCreation(void);
	/*!
	* \fn testChangeCellType
	* \brief function to test that the map grid is malleable
	*/
	void testChangeCellType(void);
	/*!
	* \fn testConvertToCellType
	* \brief function to test that the function ConvertToCellType return the correct cell type enum
	*/
	void testConvertToCellType(void);
	/*!
	* \fn testPath
	* \brief function to test that the function IsTherePath correctly asserts that there is a possible path in a map 
	*/
	void testPath(void);
	/*!
	* \fn testValidCell
	* \brief function to test that the function ValidCell correctly asserts if the next checked cell is valid
	*/
	void testValidCell(void);
private:
	/*!
	* \var mapWithParams
	* \brief variable for a pointer to a simple map
	*/
	Map::Map* mapWithParams;
	/*!
	* \var mapNoPath
	* \brief variable for a pointer to a map with no possible path
	*/
	Map::Map* mapNoPath;
	/*!
	* \var mapLongPath
	* \brief variable for a pointer to a map with a long possible path
	*/
	Map::Map* mapLongPath;
	/*!
	* \var mapEmpty
	* \brief variable for a pointer to a map with all empty cells
	*/
	Map::Map* mapEmpty;
	/*!
	* \var visitedEmpty
	* \brief variable for a std::vector of visited cells for mapEmpty used in ValidCell
	*/
	std::vector<std::vector<bool>> visitedEmpty;
	/*!
	* \var visited
	* \brief variable for a std::vector of visited cells for mapNoPath used in ValidCell
	*/
	std::vector<std::vector<bool>> visited;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestMap);
