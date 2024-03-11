#include "MapBuilder.h"
#include "RawMapBuilder.h"
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

		}
	}
	catch (const ofstream::failure& e) {
		cout << "Exception caught while opening file: " << filename << endl;
	}

	file.close()




}

Map::Map* LoadMap(std::string& filename) {







}

