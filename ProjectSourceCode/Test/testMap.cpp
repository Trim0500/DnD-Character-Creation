///*!
//* \file testMap.cpp
//* \brief Test implementation for Map
//*/
//
//#include <iostream>
//#include <string>
//#include <sstream>
//
//#include "testMap.h"
//
//void TestMap::setUp(void)
//{
//	mapWithParams = new Map::Map(5, 4);
//	mapWithParams->ChangeCell(1, 1, Map::Cell_Type::wall);
//
//	mapNoPath = new Map::Map(10, 10);
//	mapNoPath->ChangeCell(0, 1, Map::Cell_Type::wall);
//	mapNoPath->ChangeCell(1, 0, Map::Cell_Type::wall);
//
//	mapLongPath = new Map::Map(5, 5);
//	mapLongPath->ChangeCell(0, 3, Map::Cell_Type::wall);
//	mapLongPath->ChangeCell(1, 1, Map::Cell_Type::wall);
//	mapLongPath->ChangeCell(1, 3, Map::Cell_Type::wall);
//	mapLongPath->ChangeCell(2, 2, Map::Cell_Type::wall);
//	mapLongPath->ChangeCell(3, 1, Map::Cell_Type::wall);
//	mapLongPath->ChangeCell(4, 3, Map::Cell_Type::wall);
//
//	mapEmpty = new Map::Map(7, 7);
//
//	visitedEmpty = std::vector<std::vector<bool>>(7, std::vector<bool>(7, false));
//	visitedEmpty[0][0] = true;
//
//	visited = std::vector<std::vector<bool>>(10, std::vector<bool>(10, false));
//	visited[0][0] = true;
//}
//
//void TestMap::tearDown(void)
//{
//	delete mapWithParams;
//	delete mapNoPath;
//	delete mapLongPath;
//	delete mapEmpty;
//}
//
//void TestMap::testConstructor(void)
//{
//	CPPUNIT_ASSERT(mapWithParams->getRows() == 5);
//	CPPUNIT_ASSERT(mapWithParams->getCols() == 4);
//	CPPUNIT_ASSERT(mapWithParams->getEnd_Cell()[0] == 4);
//	CPPUNIT_ASSERT(mapWithParams->getEnd_Cell()[1] == 3);
//	CPPUNIT_ASSERT(mapWithParams->Grid().size() == 5);
//	CPPUNIT_ASSERT(mapWithParams->Grid()[0].size() == 4);
//}
//
//void TestMap::testGetRows(void)
//{
//	CPPUNIT_ASSERT(mapWithParams->getRows() == 5);
//}
//
//void TestMap::testGetCols(void)
//{
//	CPPUNIT_ASSERT(mapWithParams->getCols() == 4);
//}
//
//void TestMap::testGetEnd_Cell(void)
//{
//	CPPUNIT_ASSERT(mapWithParams->getEnd_Cell()[0] == 4);
//	CPPUNIT_ASSERT(mapWithParams->getEnd_Cell()[1] == 3);
//}
//
//void TestMap::testGetGrid(void)
//{
//	CPPUNIT_ASSERT(mapWithParams->Grid().size() == 5);
//	CPPUNIT_ASSERT(mapWithParams->Grid()[0].size() == 4);
//}
//
//void TestMap::testGridCreation(void)
//{
//	CPPUNIT_ASSERT(mapWithParams->Grid()[0][0] == Map::Cell_Type::empty);
//	CPPUNIT_ASSERT(mapWithParams->Grid()[0][1] == Map::Cell_Type::empty);
//	CPPUNIT_ASSERT(mapWithParams->Grid()[2][2] == Map::Cell_Type::empty);
//	CPPUNIT_ASSERT(mapWithParams->Grid()[2][3] == Map::Cell_Type::empty);
//	CPPUNIT_ASSERT(mapWithParams->Grid()[2][2] != Map::Cell_Type::wall);
//}
//
//void TestMap::testChangeCellType(void)
//{
//	CPPUNIT_ASSERT(mapWithParams->Grid()[1][1] == Map::Cell_Type::wall);
//}
//
//void TestMap::testConvertToCellType(void)
//{
//	CPPUNIT_ASSERT(Map::ConvertToCellType('e') == Map::Cell_Type::empty);
//	CPPUNIT_ASSERT(Map::ConvertToCellType('w') == Map::Cell_Type::wall);
//	CPPUNIT_ASSERT(Map::ConvertToCellType('s') == Map::Cell_Type::special);
//	CPPUNIT_ASSERT(Map::ConvertToCellType('p') == Map::Cell_Type::empty);
//}
//
//void TestMap::testPath(void)
//{
//	CPPUNIT_ASSERT(mapWithParams->IsTherePath() == true);
//	CPPUNIT_ASSERT(mapNoPath->IsTherePath() == false);
//	CPPUNIT_ASSERT(mapLongPath->IsTherePath() == true);
//}
//
//void TestMap::testValidCell(void)
//{ 
//	CPPUNIT_ASSERT(mapEmpty->ValidCell(0, 1, visitedEmpty) == true);
//	CPPUNIT_ASSERT(mapEmpty->ValidCell(-1, 0, visitedEmpty) == false);
//	CPPUNIT_ASSERT(mapEmpty->ValidCell(0, -1, visitedEmpty) == false);
//	CPPUNIT_ASSERT(mapEmpty->ValidCell(0, 8, visitedEmpty) == false);
//	CPPUNIT_ASSERT(mapEmpty->ValidCell(8, 0, visitedEmpty) == false);
//
//	CPPUNIT_ASSERT(mapNoPath->ValidCell(0, 1, visited) == false);
//}