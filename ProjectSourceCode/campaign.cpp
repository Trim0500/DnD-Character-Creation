/*!
* \file Campaign.cpp
* \brief Implementation class of the editable Campaign
* 
* \author Tristan Lafleur
*/

#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>

#include "Campaign.h"

namespace {
    /*!
    * \fn FindMapByID
    * \brief Helper function to find the Map instance pointer in a Map instnace pointer vector
    * 
    * \param _mapID Address of a constant integer that represents the ID key
    * \param _mapVector Address of a constant vector of Map instance pointers that represents vetcor to search
    * 
    * \return The pointer to a Map instance
    * 
    * \throw exception
    */
    Map::Map* FindMapByID(const int& _mapID, const std::vector<Map::Map*>& _mapVector) {
        auto foundMap = std::find_if(_mapVector.begin(),
                                        _mapVector.end(),
                                        [_mapID](Map::Map* map){return map->GetMapID() == _mapID;});
        if (foundMap == _mapVector.end()) {
            throw std::exception("Failed to find the map w/ID: " + _mapID);
        }

        return (*foundMap);
    }

    /*!
    * \fn BuildCampaignRecord
    * \brief Helper function to build a CampaignRecord to be used to save to a file
    */
    campaign::CampaignRecord BuildCampaignRecord(campaign::Campaign _campaign) {
        campaign::CampaignRecord result;

        result.campaignID = *_campaign.GetCampaignID();
        result.numRows = _campaign.GetMapIDs()->size();
        result.numCols = _campaign.GetMapIDs()->at(0).size();
        result.mapIDs = *_campaign.GetMapIDs();
        result.currentMapID = _campaign.GetCurrentMap()->mapID;
        result.currentMapXCoor = _campaign.GetCurrentMap()->coorX;
        result.currentMapYCoor = _campaign.GetCurrentMap()->coorY;

        std::vector<int> includedMapIDs;

        std::vector<Map::Map*>* mapsInCampaign = _campaign.GetMapsInCampaign();
        for (int i = 0; i < (int)mapsInCampaign->size(); ++i)
        {
            includedMapIDs.push_back(mapsInCampaign->at(i)->GetMapID());
        }
        
        result.mapsInCampaign = includedMapIDs;

        return result;
    }

    std::string BuildCampaignCSVContent(campaign::CampaignRecord _campaignRecord) {
        std::ostringstream mapIDsString;
        mapIDsString << "[";
        
        std::vector<std::vector<int>> mapIDs = _campaignRecord.mapIDs;
        for (int i = 0; i < (int)mapIDs.size(); ++i)
        {
            for (int j = 0; j < (int)mapIDs[i].size(); ++j)
            {
                if (i + 1 == mapIDs.size() && j + 1 == mapIDs[i].size()) {
                    mapIDsString << "{" << i << ";" << j << ";" << mapIDs[i][j] << "}";

                    break;    
                }

                mapIDsString << "{" << i << ";" << j << ";" << mapIDs[i][j] << "}:";
            }
            
        }

        mapIDsString << "]";

        std::ostringstream mapsInCampaignString;
        mapsInCampaignString << "[";
        
        std::vector<int> mapsInCampaign = _campaignRecord.mapsInCampaign;
        for (int i = 0; i < (int)mapsInCampaign.size(); ++i)
        {
            if (i + 1 == mapsInCampaign.size()) {
                mapsInCampaignString << mapsInCampaign[i];

                break;
            }

            mapsInCampaignString << mapsInCampaign[i] << ":";
        }
        
        mapsInCampaignString << "]";

        std::ostringstream result;
        result << _campaignRecord.campaignID
                << _campaignRecord.numRows
                << _campaignRecord.numCols
                << mapIDsString.str()
                << _campaignRecord.currentMapID
                << _campaignRecord.currentMapXCoor
                << _campaignRecord.currentMapYCoor
                << mapsInCampaignString.str();

        return result.str();
    }
}

namespace campaign {
    Campaign::Campaign(){};

    Campaign::Campaign(const int& _rows, const int& _cols) {
        std::vector<std::vector<int>> newMapIDMatrix;
        for (int i = 0; i < _rows; ++i)
        {
            std::vector<int> columnIDs;
            for (int j = 0; j < _cols; ++j)
            {
                columnIDs.push_back(0);
            }
            newMapIDMatrix.push_back(columnIDs);
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
        if ((_coordX < 1 || _coordX > (int)mapIDs.size()) || (_coordY < 1 || _coordY > mapIDs[_coordX - 1].size())) {
            std::ostringstream message;
            message << "Invalid coordiantes: " << _coordX << "," << _coordY;
            throw std::invalid_argument(message.str());
        }
        
        int foundMapID = mapIDs[_coordX - 1][_coordY - 1];
        Map::Map* result = FindMapByID(foundMapID, mapsInCampaign);

        currentMap.mapID = result->GetMapID();
        currentMap.coorX = _coordX;
        currentMap.coorX = _coordY;

        return result;
    }

    void SaveCampaigns(const std::string& _folderDir, Campaign _campaignToSave) {
        std::ostringstream fileNamePattern;
        fileNamePattern << "Campaign" << *_campaignToSave.GetCampaignID() << ".csv";

        ostringstream fullURI;
        fullURI << _folderDir << "\\" << fileNamePattern.str();

        CampaignRecord recordToSave = BuildCampaignRecord(_campaignToSave);

        std::string csvOutput = BuildCampaignCSVContent(recordToSave);

        std::ofstream campaignFile(fullURI.str());
        campaignFile << csvOutput;
    }
}
