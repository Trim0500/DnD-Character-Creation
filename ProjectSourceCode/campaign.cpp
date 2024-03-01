/*!
* \file Campaign.cpp
* \brief Implementation class of the editable Campaign
* 
* \author Tristan Lafleur
*/

#include <algorithm>

#include "Campaign.h"

namespace {

}

namespace campaign {
    Campaign::Campaign(){};

    Campaign::Campaign(const int& _rows, const int& _cols) {
        std::vector<std::vector<int>> newMapIDMatrix;
        for (int i = 0; i < _rows; ++i)
        {
            for (int j = 0; j < _cols; ++j)
            {
                newMapIDMatrix[i].push_back(0);
            }
        }
        mapIDs = newMapIDMatrix;
        currentMap.mapID = 0;
        currentMap.coorX = 0;
        currentMap.coorY = 0;
    }

    Campaign::Campaign(std::vector<std::vector<int>> _mapMatrix, CampaignMap _currentMap, std::vector<Map::Map*> _mapsInCampaign) {
        mapIDs = _mapMatrix;
        currentMap = _currentMap;
        mapsInCampaign = _mapsInCampaign;
    }

    Map::Map* Campaign::GetMap(const int& _coordX, const int& _coordY) {
        int foundMapID = mapIDs[_coordX][_coordY];

        auto foundMap = std::find_if(mapsInCampaign.begin(),
                                        mapsInCampaign.end(),
                                        [foundMapID](Map::Map* map){return map->GetMapID() == foundMapID;});
        if (foundMap == mapsInCampaign.end()) {
            // throw exception, should be noted in docs
        }

        Map::Map* result = (*foundMap);

        currentMap.mapID = result->GetMapID();
        currentMap.coorX = _coordX;
        currentMap.coorX = _coordY;

        return result;
    }
}
