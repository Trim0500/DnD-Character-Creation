#include <fstream>
#include <iostream>
#include <string>
#include<iostream>
#include<vector>
#include<sstream>

#include "MapBuilder.h"
#include "..\Character\Character.h"
#include "..\Interactable\EmptyCell.h"
#include "..\Item\item.h"
#include "..\Interactable\Wall.h"
#include "..\Door\door.h"

using namespace door;

bool MapBuilder::MapBuilder::SaveMap(Map::Map* map, std::string& filename) {
	//create file
	std::ofstream file(filename);
	try {
		//open file
		if (!file.is_open()) {
			std::cout << "Could not open file: " << filename << std::endl;
			return false;
		}
		else{
			file << map->GetMapID()
					<< ","
					<< map->getRows()
					<< ","
					<< map->getCols()
					<< ","
					<< map->getStartCell()[0]
					<< ","
					<< map->getStartCell()[1]
					<< ","
					<< map->getEndCell()[0]
					<< ","
					<< map->getEndCell()[1]
					<< std::endl;

			//loop throug the map and save each non-empty cell

			for (int i = 0; i < map->getGrid().size(); i++) {
				for (int j = 0; j < map->getGrid()[i].size(); j++) {
					file << i << "," << j;
					Interactable::Interactable* valueAtCell = map->getGrid()[i][j];
					if (dynamic_cast<Wall*>(valueAtCell)) {
						file << ",w" << std::endl;
					}
					else if (dynamic_cast<Character::Character*>(valueAtCell)) {
						file << ",c," << static_cast<Character::Character*>(valueAtCell)->ID() << std::endl;
					}
					else if (dynamic_cast<Door*>(valueAtCell)) {
						file << ",d," << static_cast<Door*>(valueAtCell)->GetDoorID() << std::endl;
					}
					else if (dynamic_cast<ItemContainer*>(valueAtCell)) {
						file << ",ic," << static_cast<ItemContainer*>(valueAtCell)->GetItemId() << std::endl;
					}
					else if (dynamic_cast<Item*>(valueAtCell)) {
						file << ",i," << static_cast<Item*>(valueAtCell)->GetItemId() << std::endl;
					}
					else {
						file << std::endl;
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

Map::Map* MapBuilder::MapBuilder::LoadMap(std::string& filename) {

	Map::Map* mapload = new Map::Map();

	std::ifstream file(filename);

	int lines = 0; //number of lines read
	int cellRow, cellCol;
	std::string type;

	try {
		//open file
		if (!file.is_open()) {
			std::cout << "Could not open file: " << filename << std::endl;
		}
		else {
			std::string line;
			//while there is content in the file
			while (getline(file, line)) {
				lines++;

				//first line create the num of rows and cols
				if (lines == 1) {
					std::vector<std::string> split;
					std::stringstream ss(line);

					while (ss.good()) {
						std::string sub;
						getline(ss, sub, ',');
						split.push_back(sub);
					}
					//row,col,SCrow,SCcol,ECrow,ECcol
					// 0 , 1 ,  2  ,  3  ,  4  , 5
					mapload->setMapID(std::stoi(split[0]));
					mapload->setRows(std::stoi(split[1]));
					mapload->setCols(std::stoi(split[2]));
					mapload->setGrid();
					mapload->setStartCell(std::stoi(split[3]), std::stoi(split[4]));
					mapload->setEndCell(std::stoi(split[5]), std::stoi(split[6]));
				}

				else {
					std::vector<std::string> split;
					std::stringstream ss(line);

					while (ss.good()) {
						std::string sub;
						getline(ss, sub, ',');
						split.push_back(sub);
					}

					cellRow = std::stoi(split[0]);
					cellCol = std::stoi(split[1]);
					if (split.size() >= 3) {
						type = split[2];
					}
					else {
						type = "";
					}

					if (type == "w") {
						mapload->setWall(cellRow, cellCol);
					}
					else if (type == "c") {
						Character::Character* c = new Character::Character(std::stoi(split[3]));
						mapload->setCharacter(cellRow, cellCol, c);
					}
					else if (type == "d") {
						Door* door = new Door(std::stoi(split[3]));
						mapload->setCell(cellRow, cellCol, door);
					}
					else if (type == "ic") {
						ItemContainer* container = new ItemContainer(std::stoi(split[3]));
						mapload->setCell(cellRow, cellCol, container);
					}
					else if (type == "i") {
						item::Item* i = new item::Item(std::stoi(split[3]));
						mapload->setItem(cellRow, cellCol, i);
					}
					else {
						mapload->setEmpty(cellRow, cellCol);
					}
				}
			}
		}
	}
	catch (const std::ifstream::failure& e) {
		std::cout << "Exception caught while opening file: " << filename << std::endl;
	}

	file.close();

	return mapload;
}