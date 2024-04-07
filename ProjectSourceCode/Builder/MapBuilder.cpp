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
#include "MapBuilder.h"
#include "..\Interactable\Wall.h"

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
					file << i << "," << j << "," << (map->getGrid()[i][j])->serialize() << std::endl;
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

Map::Map MapBuilder::MapBuilder::LoadMap(std::string& filename) {

	Map::Map mapload = Map::Map();

	std::ifstream file(filename);

	int lines = 0; //number of lines read
	int row = 0;
	int col = 0;
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
				std::cout << line << std::endl;

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

					row = std::stoi(split[0]);
					col = std::stoi(split[1]);

					mapload.setCols(col);
					mapload.setRows(row);
					mapload.setGrid();
				}

				else {
					std::vector<std::string> split;
					std::stringstream ss(line);

					while (ss.good()) {
						std::string sub;
						getline(ss, sub, ',');
						split.push_back(sub);
					}

					row = std::stoi(split[0]);
					col = std::stoi(split[1]);
					type = split[2];

					if (type == "w") {
						mapload.setWall(row, col);
					}
					/*else if (type == "c") {
						//TODO? handled outside of here
					}*/

				}

			}
		}


	}
	catch (const std::ifstream::failure& e) {
		std::cout << "Exception caught while opening file: " << filename << std::endl;
	}

	return mapload;
}