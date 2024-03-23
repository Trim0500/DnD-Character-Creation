#include "MapBuilder.h"
#include "Character.h"
#include "EmptyCell.h"
#include "Item.h"
#include "MapBuilder.h"
#include "RawMapBuilder.h"
#include "Wall.h"
#include <fstream>
#include <iostream>
#include <string>

void  RawMapBuilder::RawMapBuilder::buildRows(int rows) {
	m_map->setRows(rows);
}

void  RawMapBuilder::RawMapBuilder::buildCols(int cols) {
	m_map->setCols(cols);
}

void  RawMapBuilder::RawMapBuilder::buildEndCell() {
	m_map->setEndCell();
}

void  RawMapBuilder::RawMapBuilder::buildGrid() {
	m_map->setGrid();
}

bool MapBuilder::MapBuilder::SaveMap(Map::Map* map, std::string& filename) {
	//create file
	std::ofstream file(filename);
	try {
		//open file
		if (!file.is_open()) {
			std::cout << "Could not open file: " << filename << std::endl;
			return false;
		}
		else {
			file << map->getRows() << "," << map->getCols() << std::endl;

			//loop throug the map and save each non-empty cell

			for (int i = 0; i < map->getGrid().size(); i++) {
				for (int j = 0; j < map->getGrid()[i].size(); j++) {
					//if wall: write the row,col and celltype
					if (typeid(map->getGrid()[i][j]) == typeid(Wall)) {
						file << i << "," << j << "w" << std::endl;
						//row,col,w
					}
					//if item
					else if (typeid(map->getGrid()[i][j]) == typeid(Item)) {
						file << i << "," << j << "i" << "," << dynamic_cast<Item*>(map->getGrid()[i][j])->GetItemId() << std::endl;
						//row,col,i,ID
					}
					// if character	
					else if (typeid(map->getGrid()[i][j]) == typeid(Character::Character)) {
						file << i << "," << j << "c" << "," << dynamic_cast<Character::Character*>(map->getGrid()[i][j])->ID() << std::endl;
						//row,col,c
					}
					//if the cell type is empty: do nothing
					else if (typeid(map->getGrid()[i][j]) == typeid(EmptyCell)) {
						file << i << "," << j << "e" << std::endl;
					}
				}
			}//end loop
		}//end file writing
	}
	catch (const std::ofstream::failure& e) {
		std::cout << "Exception caught while opening file: " << filename << std::endl;
	}

	file.close();
	return true;
}

Map::Map RawMapBuilder::RawMapBuilder::LoadMap(std::string& filename) {

	Map::Map mapload = Map::Map();

	std::ifstream file(filename);

	try {
		//open file
		if (!file.is_open()) {
			std::cout << "Could not open file: " << filename << std::endl;
		}
		else {
			std::string line;
			//while there is content in the file
			while (getline(file, line)) {

				// hereee build 
			}
		}


	}
	catch (const std::ifstream::failure& e) {
		std::cout << "Exception caught while opening file: " << filename << std::endl;
	}

	return mapload;
}