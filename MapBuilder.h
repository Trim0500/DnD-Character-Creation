#pragma once

#include "ProjectSourceCode/Map.h"

namespace MapBuilder {

	class MapBuilder {

	public:
		// get built Map from Builder
		Map::Map* getMap() { return m_map; }
		//build generic void Map
		void createnewMap() { m_map = new Map::Map; }
		//create all parts
		virtual void buildRows() = 0;
		virtual void buildCols() = 0;
		virtual void buildGrid() = 0;
		virtual void buildEmpty() = 0;
		virtual void buildWall() = 0;
		virtual void buildSpecial() = 0;

	protected:
		//Product built by Builder
		Map::Map* m_map;
	};
}