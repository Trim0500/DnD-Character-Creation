//#include "Character.h"
//#include "EmptyCell.h"
//#include "Item.h"
//#include "MapBuilder.h"
//#include "RawMapBuilder.h"
//#include "Wall.h"
//#include <fstream>
//#include <iostream>
//#include <string>
//
//void  RawMapBuilder::RawMapBuilder::buildRows(int rows) {
//	m_map->setRows(rows);
//}
//
//void  RawMapBuilder::RawMapBuilder::buildCols(int cols) {
//	m_map->setCols(cols);
//}
//
//void  RawMapBuilder::RawMapBuilder::buildEndCell() {
//	m_map->setEndCell();
//}
//
//void  RawMapBuilder::RawMapBuilder::buildGrid() {
//	m_map->setGrid();
//}
//
////void RMP::buildTypes() {
////	
////}
//
//bool RawMapBuilder::RawMapBuilder::SaveMap(Map::Map* map, std::string& filename) {
//	//create file
//	ofstream file(filename);
//	try {
//		//open file
//		if (!file.is_open()) {
//			cout << "Could not open file: " << filename << endl;
//			return false;
//		}
//		else {
//			file << map->getRows() << "," << map->getCols() << endl;
//
//			//loop throug the map and save each non-empty cell
//
//			for (int i = 0; i < map->getGrid().size(); i++) {
//				for (int j = 0; j < map->getGrid()[i].size(); j++) {
//					//if wall: write the row,col and celltype
//					if (typeid(map->getGrid()[i][j]) == typeid(Wall)) {
//						file << i << "," << j << "w" << endl;
//						//row,col,w
//					}
//					//if item
//					else if (typeid(map->getGrid()[i][j]) == typeid(Item)) {
//						file << i << "," << j << "i" << "," << dynamic_cast<Item*>(map->getGrid()[i][j])->GetItemId() << endl;
//						//row,col,i,ID
//					}
//					// if character	
//					else if (typeid(map->getGrid()[i][j]) == typeid(Character::Character)) {
//						file << i << "," << j << "c" << "," << dynamic_cast<Character::Character*>(map->getGrid()[i][j])->ID() << endl;
//						//row,col,c
//					}
//					//if the cell type is empty: do nothing
//					else if (typeid(map->getGrid()[i][j]) == typeid(EmptyCell)) {
//						file << i << "," << j << "e" << endl;
//					}
//				}
//			}//end loop
//		}//end file writing
//	}
//	catch (const ofstream::failure& e) {
//		cout << "Exception caught while opening file: " << filename << endl;
//	}
//
//	file.close();
//	return true;
//}
//
//Map::Map RawMapBuilder::RawMapBuilder::LoadMap(std::string& filename) {
//	//USE BUILD FUNCTIONS IN HERE
//
//	Map::Map mapload = Map::Map();
//
//	ifstream file(filename);
//
//	try {
//		//open file
//		if (!file.is_open()) {
//			cout << "Could not open file: " << filename << endl;
//		}
//		else {
//			string line;
//			//while there is content in the file
//			while (getline(file, line)) {
//
//				// hereee build 
//			}
//		}
//
//
//	}
//	catch (const ifstream::failure& e) {
//		cout << "Exception caught while opening file: " << filename << endl;
//	}
//
//	return mapload;
//}
//
