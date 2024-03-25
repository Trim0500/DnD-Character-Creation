#pragma once
#include "Map.h"
#include <string>

// using namespace std; // can't be used with GUI


namespace MapBuilder {

	class MapBuilder {

	public:
		// get built Map from Builder
		Map::Map* getMap() { return m_map; }
		//build generic void Map
		void createnewMap() { m_map = new Map::Map(); }

		//save map object to a file
		static bool SaveMap(Map::Map* map, std::string& filename);
		//load map from a text file
		static Map::Map LoadMap(std::string& filename);

		//create all parts
		void buildRows(int r);
		void buildCols(int c);
		void buildGrid();
		void buildEndCell();
		//void buildTypes();

	protected:
		//Product built by Builder
		Map::Map* m_map;
	};
}