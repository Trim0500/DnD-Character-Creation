#include "MapBuilder.h"
#include "MapDirector.h"

using MD = MapDirector::MapDirector;
using MB = MapBuilder::MapBuilder;

void MD::setMapBuilder(MB* mb) {
	m_mapBuilder = mb;
}

Map::Map* MD::getMap() {
	return m_mapBuilder->getMap();
}

void MD::constructMap() {
	m_mapBuilder->createnewMap();
	//more to come?
}
