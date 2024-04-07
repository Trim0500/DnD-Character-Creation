//#include <iostream>
//#include <fstream>
//
//#include "MapSerializer.h"
//#include "../ProjectSourceCode/Map/Map.h"
//
//
//namespace CampaignEditor {
//	struct Cell {
//		int x;
//		int y;
//		Map::Cell_Type ct;
//	};
//
//	
//	Map::Map MapSerializer::load_map(std::string& filename) {
//		/* int map_id;
//		int map_x_size;
//		int map_y_size;
//		std::ifstream MapFile(filename);
//		std::string line;
//		int i = 0;
//
//		// while (std::getline (MapFile, line)) {
//		// 	if (i == 0){
//		// 		map_id = std::stoi(i);
//		// 		continue;
//		// 	}
//		// 	if (i == 1) {
//				
//		// 		continue;
//		// 	}
//
//			
//		// }
//		MapFile.close();
//
//		 */
//		Map::Map m = Map::Map(5,5);
//		return m;
//	}
//
//	bool MapSerializer::save_map(std::string&filename, Map::Map *m){
//		std::ofstream MapFile(filename);
//		MapFile << m->GetMapID() << std::endl;
//		MapFile << m->Cols() << "," << m->Rows() << std::endl;
//		for (int j = 0; j < m->Rows(); j++){
//			for (int i = 0; i<m->Cols(); i++){
//				MapFile << i << "," << j << "," << static_cast<int>(m->Grid()[j][i]) << std::endl;
//			}
//		}
//		MapFile.close();
//		return true;
//	}
//
//}