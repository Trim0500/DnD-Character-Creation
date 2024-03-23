#pragma once
#include "Map.h"
#include <string>
<<<<<<< HEAD
=======

// using namespace std; // can't be used with GUI

>>>>>>> e48c3efde6b37d850058987a2bdc28da07358e64

namespace MapBuilder {

	class MapBuilder {

	public:
		// get built Map from Builder
		Map::Map* getMap() { return m_map; }
		//build generic void Map
<<<<<<< HEAD
		void createnewMap() { m_map = new Map::Map(); }
=======
		void createnewMap() { m_map = new Map::Map; }

>>>>>>> e48c3efde6b37d850058987a2bdc28da07358e64

		//save map object to a file
		static bool SaveMap(Map::Map* map, std::string& filename);
		//load map from a text file
<<<<<<< HEAD
		static Map::Map LoadMap(std::string& filename);
=======
		virtual Map::Map LoadMap(std::string& filename);
>>>>>>> e48c3efde6b37d850058987a2bdc28da07358e64

		//create all parts
		void buildRows();
		void buildCols();
		void buildGrid();
		void buildEndCell();
		void buildTypes();

	protected:
		//Product built by Builder
		Map::Map* m_map;
	};
}