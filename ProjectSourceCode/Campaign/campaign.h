/*!
* \file campaign.h
* \brief Class that abstracts the functionality for the main editable campaigns
*
* @author Tristan Lafleur (40245238)
*/

#pragma once

#include <vector>

#include "..\Map\Map.h"

/*!
* \namespace campaign
* \brief Namespace to partition the Campaign functionality
*/
namespace campaign {
    /*!
    * \struct CampaignMap
    * \brief Struct to represent the current map selected when editing the campaign
    */
    struct CampaignMap
    {
        int mapID;
        int coorX;
        int coorY;
    };

    /*!
    * \struct CampaignRecord
    * \brief Struct that represents the serialized Campaign format to save & load
    */
    struct CampaignRecord {
        int campaignID;
        int numRows;
        int numCols;
        std::vector<std::vector<int>> mapIDs;
        int currentMapID;
        int currentMapXCoor;
        int currentMapYCoor;
        std::vector<int> mapsInCampaign;
    };

    /*!
    * \class Campaign
    * \brief Class to abstract the campaign functionality
    */
    class Campaign {
        public:
            /*!
            * \fn Campaign
            * \brief No-args constructor for Campaign
            */
            Campaign();

            /*!
            * \fn Campaign
            * \brief Overloaded constructor to create a new campaign
            * 
            * \param _rows Integer that represents the number of rows for matrix
            * \param _cols Integer that represents the number of cols for matrix
            */
            Campaign(const int&, const int&);

            /*!
            * \fn Campaign
            * \brief Overloaded constructor to when loading a campaign
            * 
            * \param _existingCampaignID Integer which represents the campaign's saved ID
            * \param _mapMatrix 2D matrix of ints that represents the campaign's map data 
            * \param _currentMap Instance of a CampaignMap struct loaded from serialization
            * \param _mapsInCampaign Vector that represents a loaded list of pointers to Map instances 
            */
            Campaign(int, const int&, const int&, std::vector<std::vector<int>>, CampaignMap, std::vector<Map::Map*>);

            int GetCurrentCampaignID() { return nextCampaignID; };

            void SetCurrentCampaignID(int _nextCampaignID) { nextCampaignID = _nextCampaignID; };

            int GetCampaignID() { return campaignID; };

            void SetCampaignID(int _campaignID) { campaignID = _campaignID; };

            int GetGridRows() { return gridRows; };

            void SetGridRows(int _gridRows) { gridRows = _gridRows; };

            int GetGridCols() { return gridCols; };

            void SetGridCols(int _gridCols) { gridCols = _gridCols; };

            std::vector<std::vector<int>> GetMapIDs() {return mapIDs;};

            CampaignMap GetCurrentMap() {return currentMap;};

            void SetCurrentMap(CampaignMap _currentMap) { currentMap = _currentMap; };

            /*!
            * \fn AddMapToCampaign
            * \brief Function to add a new Map instance to the campaign and set the ID at the cell
            * 
            * \param _row Integer that represents the 1-indexed row number 
            * \param _col Integer that represents the 1-indexed column number 
            * \param _mapToAdd Map instance that represents the map to insert into the cell
            * 
            * \throw exception
            * \throw invalid_argument
            */
            void AddMapToCampaign(const int&, const int&, Map::Map&);

            std::vector<Map::Map*> GetMapsInCampaign() {return mapsInCampaign;};

            /*!
            * \fn GetMap
            * \brief Function to find the map data at the specified coordinates (Coordiantes should be 1-indexed)
            * 
            * \param _coordX Integer that represents the x coordiante to look for in the matrix
            * \param _coordY Integer that represents the y coordiante to look for in the matrix
            * 
            * \return Pointer to a map instance in the campaign at the specified coordiantes
            * 
            * \throw exception
            * \throw invalid_argument
            */
            Map::Map* GetMap(const int&, const int&);
        private:
            static inline int nextCampaignID = 0;

            /*!
            * \var campaignID
            * \brief Integer representing the unique ID for a Campaign
            */
            int campaignID;

            /*!
            * \var gridRows
            * \brief Integer representing the number of rows in the campaign grid
            */
            int gridRows;

            /*!
            * \var gridCols
            * \brief Integer representing the number of cols in the campaign grid
            */
            int gridCols;

            /*!
            * \var mapIDs
            * \brief A matrix of ints that represents the relative positions of the maps in a campaign
            */
            std::vector<std::vector<int>> mapIDs;
            
            /*!
            * \var currentMap
            * \brief Instance of the CampaignMap struct to represent the current map shown/loaded
            */
            CampaignMap currentMap;
            
            /*!
            * \var mapsInCampaign
            * \brief Vector that represents the pointers to Map instances that the maps that exist in the campaign
            */
            std::vector<Map::Map*> mapsInCampaign;
    };

    /*!
    * \fn SaveCampaigns 
    * \brief Function to save instances of created campaigns into a CSV file.
    * 
    * \param _folderDir String that represents the absolute path of the directory to save the contents to (Do not append with slash)
    * \param _campaignToSave Campaign instance that represents the current campaign the user wants to save the edits
    */
    void SaveCampaigns(const std::string&, Campaign);

    /*!
    * \fn LoadCampaigns 
    * \brief Function to load instances of created campaigns from a CSV file.
    * 
    * \param _campaignID String that represents the absolute path of the directory to save the contents to (Do not append with slash)
    * \param _folderDir String that represents the absolute path of the directory to save the contents to (Do not append with slash)
    * 
    * \return Pointer to a CampaignRecord struct that represents the selecetd campaing to use
    * 
    * \throw invalid_argument
    */
    CampaignRecord* LoadCampaign(const int&, const std::string&);
}
