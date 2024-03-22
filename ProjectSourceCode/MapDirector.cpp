#include "MapBuilder.h"
#include "MapDirector.h"

namespace MapDirector {
	void MapDirector::setMapBuilder(MapBuilder::MapBuilder* mb) {
		m_mapBuilder = mb;
	}

	Map::Map* MapDirector::getMap() {
		return m_mapBuilder->getMap();
	}

	void MapDirector::constructMap() {
		m_mapBuilder->createnewMap();
		//more to come?
	}
}
