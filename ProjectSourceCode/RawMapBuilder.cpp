#include "Character.h"
#include "EmptyCell.h"
#include "Item.h"
#include "MapBuilder.h"
#include "RawMapBuilder.h"
#include "Wall.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
using RMP = RawMapBuilder::RawMapBuilder;

void RMP::buildRows(int rows) {
	m_map->setRows(rows);
}

void RMP::buildCols(int cols) {
	m_map->setCols(cols);
}

void RMP::buildEndCell() {
	m_map->setEndCell();
}

void RMP::buildGrid() {
	m_map->setGrid();
}

void RMP::buildTypes() {
	//m_map->setEmpty(row, col);
	//TODO
}

bool SaveMap(Map::Map* map, std::string& filename) {
	//create file
	ofstream file(filename);
	try {
		//open file
		if (!file.is_open()) {
			cout << "Could not open file: " << filename << endl;
		}
		else {
			file << map->getRows() << "," << map->getCols() << endl;

			//loop throug the map and save each non-empty cell

			for (int i = 0; i < map->getGrid().size(); i++) {
				for (int j = 0; j < map->getGrid()[i].size(); j++) {
					//if wall: write the row,col and celltype
					if (typeid(map->getGrid()[i][j]) == typeid(Wall)) {
						file << i << "," << j << "w" << endl;
						//row,col,w
					}
					//if item
					else if (typeid(map->getGrid()[i][j]) == typeid(Item)) {
						file << i << "," << j << "i" << endl;
						//file<< map->getGrid()[i][j]).serializeItem? idk how to use the serialize item 
						//row,col,i
						//everything about the item 
					}
					// if character	
					else if (typeid(map->getGrid()[i][j]) == typeid(Character::Character)) {
						file << i << "," << j << "c" << endl;
						//file<< map->getGrid()[i][j]).serializeItem? idk how to use the serialize item 
						//row,col,c
					}
					//if the cell type is empty: do nothing
					/*if (typeid(map->getGrid()[i][j]) == typeid(EmptyCell)) {

					}*/
				}
			}//end loop
		}//end file writing
		file.close();
	}
	catch (const ofstream::failure& e) {
		cout << "Exception caught while opening file: " << filename << endl;
	}

	file.close();
}

Map::Map* LoadMap(std::string& filename) {







}

