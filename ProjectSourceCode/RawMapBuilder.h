#pragma once

#include "MapBuilder.h"
<<<<<<< HEAD
=======
// using namespace std; cannot be used with GUI

>>>>>>> e48c3efde6b37d850058987a2bdc28da07358e64

namespace RawMapBuilder {

	class RawMapBuilder : public MapBuilder::MapBuilder {

	public:
		//save map object to a file
		virtual bool SaveMap(Map::Map* map, std::string& filename);
		//load map from a text file
<<<<<<< HEAD
		virtual Map::Map LoadMap(std::string& filename);
=======

		virtual Map::Map LoadMap(std::string& filename);

>>>>>>> e48c3efde6b37d850058987a2bdc28da07358e64

		virtual void buildRows(int rows);

		virtual void buildCols(int cols);

		virtual void buildEndCell();

		virtual void buildGrid();
<<<<<<< HEAD
=======

		//virtual void buildTypes();

>>>>>>> e48c3efde6b37d850058987a2bdc28da07358e64
	};
}