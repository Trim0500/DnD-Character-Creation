/*!
* \file Campaign.cpp
* \brief Implementation class of the editable Campaign
* 
* \author Tristan Lafleur (40245238)
*/

#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>

#include "Campaign.h"

using namespace campaign;

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
    * 
    * \param _campaign Campaign Instance to base the record off of.
    * 
    * \return Instance of the CampaignRecord struct housing the information about the campaign to save
    */
    CampaignRecord BuildCampaignRecord(Campaign _campaign) {
        CampaignRecord result;

        result.campaignID = _campaign.GetCampaignID();
        result.numRows = _campaign.GetMapIDs().size();
        result.numCols = _campaign.GetMapIDs().at(0).size();
        result.mapIDs = _campaign.GetMapIDs();
        result.currentMapID = _campaign.GetCurrentMap().mapID;
        result.currentMapXCoor = _campaign.GetCurrentMap().coorX;
        result.currentMapYCoor = _campaign.GetCurrentMap().coorY;

        std::vector<int> includedMapIDs;

        std::vector<Map::Map*> mapsInCampaign = _campaign.GetMapsInCampaign();
        for (int i = 0; i < (int)mapsInCampaign.size(); ++i)
        {
            includedMapIDs.push_back(mapsInCampaign.at(i)->GetMapID());
        }
        
        result.mapsInCampaign = includedMapIDs;

        return result;
    }

    /*!
    * \fn BuildCampaignCSVContent
    * \brief Helper function to create the CSV output for the file.
    * 
    * \param _campaignRecord Instance of the CampaignRecord struct that represents the data to serialize into the file
    * 
    * \return String that represents the CSV formatted output
    */
    std::string BuildCampaignCSVContent(CampaignRecord _campaignRecord) {
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
                << ","
                << _campaignRecord.numRows
                << ","
                << _campaignRecord.numCols
                << ","
                << mapIDsString.str()
                << ","
                << _campaignRecord.currentMapID
                << ","
                << _campaignRecord.currentMapXCoor
                << ","
                << _campaignRecord.currentMapYCoor
                << ","
                << mapsInCampaignString.str();

        return result.str();
    }

    /*!
    * \fn LoadCampaignRecord
    * \brief Heper function to use a saved Campaign file stream to load the data into memory
    * 
    * \param _fileStream Pointer to the saved CampaignRecord file stream to parse and load into memory
    * 
    * \return Pointer to an instance of the CampaignRecord struct that represents the loaded Campaign
    */
    CampaignRecord* LoadCampaignRecord(std::ifstream* _fileStream) {
        CampaignRecord* result = new CampaignRecord;

        while (!_fileStream->eof()) {
			std::string nextLine = "";
			std::getline(*_fileStream, nextLine);

            if (nextLine.empty()) {
                continue;
            }
            
            std::stringstream lineStream(nextLine);

			std::vector<std::string> segmentList;

			std::string segment = "";
			while (std::getline(lineStream, segment, ',')) {
				segmentList.push_back(segment);
			}

			result->campaignID = std::stoi(segmentList[0]);
			result->numRows = std::stoi(segmentList[1]);
			result->numCols = std::stoi(segmentList[2]);

            std::vector<std::vector<int>> mapIDs;
            for (int i = 0; i < result->numRows; ++i)
            {
                std::vector<int> colIDs;

                for (int j = 0; j < result->numCols; ++j)
                {
                    colIDs.push_back(0);
                }

                mapIDs.push_back(colIDs);
            }
            

			std::regex numberRgx("[0-9]+");

            std::smatch mapCellValueMatch;

			std::regex mapIDCellRgx("\\{[0-9]+;[0-9]+;[0-9]+\\}");
            while(std::regex_search(segmentList[3], mapCellValueMatch, mapIDCellRgx)) {
                std::string cellValueString = mapCellValueMatch.str();

                std::vector<int> cellValueInfo;

                std::smatch numMatch;
                while (std::regex_search(cellValueString, numMatch, numberRgx)) {
                    cellValueInfo.push_back(std::stoi(numMatch.str()));
                    
                    cellValueString = numMatch.suffix().str();
                }

                mapIDs[cellValueInfo[0]][cellValueInfo[1]] = cellValueInfo[2];

                segmentList[3] = mapCellValueMatch.suffix().str();
            }

            result->mapIDs = mapIDs;
			result->currentMapID = std::stoi(segmentList[4]);
			result->currentMapXCoor = std::stoi(segmentList[5]);
			result->currentMapYCoor = std::stoi(segmentList[6]);

			std::smatch mapIDInCampaignMatch;
			while (std::regex_search(segmentList[7], mapIDInCampaignMatch, numberRgx)) {
				result->mapsInCampaign.push_back(stoi(mapIDInCampaignMatch.str()));

				segmentList[7] = mapIDInCampaignMatch.suffix().str();
			}
		}

        return result;
    }
}

namespace campaign {
    Campaign::Campaign(){};

    Campaign::Campaign(const int& _rows, const int& _cols) {
        nextCampaignID += 1;
        campaignID = nextCampaignID;
        gridRows = _rows;
        gridCols = _cols;

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

        std::vector<Map::Map*> emptyMapsInCampaignVector;
        mapsInCampaign = emptyMapsInCampaignVector;
    }

    Campaign::Campaign(int _existingCampaignID,
                        const int& _rows,
                        const int& _cols,
                        std::vector<std::vector<int>> _mapMatrix,
                        CampaignMap _currentMap,
                        std::vector<Map::Map*> _mapsInCampaign) {
        campaignID = _existingCampaignID;
        gridRows = _rows;
        gridCols = _cols;
        mapIDs = _mapMatrix;
        currentMap = _currentMap;
        mapsInCampaign = _mapsInCampaign;
    }

    void Campaign::AddMapToCampaign(const int& _row, const int& _col, Map::Map& _mapToAdd) {
        if (mapsInCampaign.size() >= mapIDs.size() * mapIDs[0].size()) {
            throw std::exception("Too many maps!");
        }
        else if ((_row < 1 || _row > (int)mapIDs.size()) || (_col < 1 || _col > mapIDs[_row - 1].size())) {
            std::ostringstream message;
            message << "Invalid coordiantes: " << _row << "," << _col;
            throw std::invalid_argument(message.str());
        }
        
        if (mapIDs[_row - 1][_col -1] == 0) {
            mapsInCampaign.push_back(&_mapToAdd);
        }
        else {
            int mapIDAtCell = mapIDs[_row - 1][_col -1];
            auto mapAtCell = std::find_if(mapsInCampaign.begin(), mapsInCampaign.end(), [mapIDAtCell](Map::Map* map){return map->GetMapID() == mapIDAtCell;});
            if (mapAtCell == mapsInCampaign.end()) {
                throw std::exception("Failed to find the map to replace through update");
            }

            mapsInCampaign.erase(mapAtCell);
            mapsInCampaign.push_back(&_mapToAdd);
        }
        
        mapIDs[_row - 1][_col - 1] = _mapToAdd.GetMapID();
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
        currentMap.coorY = _coordY;

        return result;
    }

    void SaveCampaigns(const std::string& _folderDir, Campaign _campaignToSave) {
        std::ostringstream fileNamePattern;
        fileNamePattern << "Campaign" << _campaignToSave.GetCampaignID() << ".csv";

        std::ostringstream fullURI;
        fullURI << _folderDir << "\\" << fileNamePattern.str();

        CampaignRecord recordToSave = BuildCampaignRecord(_campaignToSave);

        std::string csvOutput = BuildCampaignCSVContent(recordToSave);

        std::ofstream campaignFile(fullURI.str());
        campaignFile << csvOutput;

        campaignFile.close();
    }

    CampaignRecord* LoadCampaign(const int& _campaignID, const std::string& _folderDir) {
        std::ostringstream fullURI;
        fullURI << _folderDir << "\\" << "Campaign" << _campaignID << ".csv";

        std::ifstream campaignFileInputStream(fullURI.str());
        if (!campaignFileInputStream.is_open()) {
			throw std::invalid_argument("Failed to open the file at: " + fullURI.str());
		}

        CampaignRecord* resultRecord = LoadCampaignRecord(&campaignFileInputStream);

        campaignFileInputStream.close();

        return resultRecord;
    }
}
