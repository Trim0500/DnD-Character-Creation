#pragma once
#include "Map.h"
#include <string>

namespace MapBuilder {

	class MapBuilder {

	public:
		// get built Map from Builder
		Map::Map* getMap() { return m_map; }
		//build generic void Map
		void createnewMap() { m_map = new Map::Map(); }

		//save map object to a file
		virtual bool SaveMap(Map::Map* map);
		//load map from a text file
		virtual Map::Map* LoadMap(std::string& filename);

		//create all parts
		virtual void buildRows() = 0;
		virtual void buildCols() = 0;
		virtual void buildGrid() = 0;
		virtual void buildEndCell() = 0;
		virtual void buildTypes() = 0;
		//virtual void buildWalls() = 0;
		//virtual void buildSpecials() = 0;

	protected:
		//Product built by Builder
		Map::Map* m_map;
	};
}