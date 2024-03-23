#include "MapBuilder.h"
#include "MapDirector.h"

<<<<<<< HEAD
=======

using MD = MapDirector::MapDirector;
>>>>>>> e48c3efde6b37d850058987a2bdc28da07358e64
using MB = MapBuilder::MapBuilder;

void MapDirector::MapDirector::setMapBuilder(MB* mb) {
	m_mapBuilder = mb;
}

Map::Map* MapDirector::MapDirector::getMap() {
	return m_mapBuilder->getMap();
}

void MapDirector::MapDirector::constructMap() {
	m_mapBuilder->createnewMap();
	//more to come?
<<<<<<< HEAD
=======

>>>>>>> e48c3efde6b37d850058987a2bdc28da07358e64
}
