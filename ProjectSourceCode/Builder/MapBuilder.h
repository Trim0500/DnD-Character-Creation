#pragma once
#include "..\Map\Map.h"
#include <string>

namespace MapBuilder {

	class MapBuilder {

	public:
		//save map object to a file
		static bool SaveMap(Map::Map* map, std::string& filename);
		//load map from a text file
		static Map::Map* LoadMap(std::string& filename);
	};
}