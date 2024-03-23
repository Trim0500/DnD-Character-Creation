#pragma once
#include "Map.h"
#include "MapBuilder.h"

namespace MapDirector {

	class MapDirector
	{
	public:
		void setMapBuilder(MapBuilder::MapBuilder* mb);

		Map::Map* getMap();

		void constructMap();//actually build the map

	private:
		MapBuilder::MapBuilder* m_mapBuilder;
	};

}
<<<<<<< HEAD
=======

>>>>>>> e48c3efde6b37d850058987a2bdc28da07358e64
