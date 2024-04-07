//#pragma once
//
//#include "MapBuilder.h"
//
//
//namespace RawMapBuilder {
//
//	class RawMapBuilder : public MapBuilder::MapBuilder {
//
//	public:
//		//save map object to a file
//		virtual bool SaveMap(Map::Map* map, std::string& filename);
//		//load map from a text file
//		virtual Map::Map LoadMap(std::string& filename);
//
//		virtual void buildRows(int rows);
//
//		virtual void buildCols(int cols);
//
//		virtual void buildEndCell();
//
//		virtual void buildGrid();
//	};
//}