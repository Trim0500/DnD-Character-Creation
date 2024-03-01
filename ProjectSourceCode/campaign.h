/*!
* \file campaign.h
* \brief Class that abstracts the functionality for the main editable campaigns
*
* @author Tristan Lafleur
*/

#pragma once

#include <vector>

#include "Map.h"

namespace campaign {
    /*!
    * \enum CampaignMap
    * \brief Enum to represent the relative data of maps in a campaign
    */
    struct CampaignMap
    {
        int mapID;
        int coorX;
        int coorY;
    };

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
            * \param _mapMatrix 2D matrix of ints that represents the campaign's map data 
            * \param _currentMap Instance of a CampaignMap struct loaded from serialization
            * \param _mapsInCampaign Vector that represents a loaded list of pointers to Map instances 
            */
            Campaign(std::vector<std::vector<int>>, CampaignMap, std::vector<Map::Map*>);
            /*!
            * \fn GetMap
            * \brief Function to find the map data at the specified coordinates
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
}
