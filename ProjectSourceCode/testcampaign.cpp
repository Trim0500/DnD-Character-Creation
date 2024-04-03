/*!
* \file testcampaign.cpp
* \brief Test implementation for Campaign
*/

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <sys/stat.h>

#include "testcampaign.h"

#define NEW_CAMPAIGN_MAPIDS_ROW_COUNT 3
#define NEW_CAMPAIGN_MAPIDS_COL_COUNT 3
#define NEW_CAMPAIGN_MAPIDS_CELL_VALUE 0
#define EXISTING_CAMPAIGN_MAPIDS_ROW_COUNT 3
#define EXISTING_CAMPAIGN_MAPIDS_COL_COUNT 3
#define EXISTING_CAMPAIGN_CURRENT_X_COOR 2
#define EXISTING_CAMPAIGN_CURRENT_Y_COOR 2
#define EXISTING_CAMPAIGN_INVALID_X_COOR 10
#define EXISTING_CAMPAIGN_INVALID_Y_COOR -10
#define EXISTING_CAMPAIGN_X_COOR 2
#define EXISTING_CAMPAIGN_Y_COOR 2
#define SAVED_CAMPAIGNS_FOLDER_NAME "\\SavedCampaigns\\TestCampaigns"
#define SAVED_CAMPAIGNS_INVALID_URI "SomePhonyURI"

void TestCampaign::setUp(void) {
    newCampaignObject = new Campaign(NEW_CAMPAIGN_MAPIDS_ROW_COUNT, NEW_CAMPAIGN_MAPIDS_COL_COUNT);

    std::vector<std::vector<int>> existingMapIDs;
    for (int i = 0; i < EXISTING_CAMPAIGN_MAPIDS_ROW_COUNT; ++i)
    {
        std::vector<int> columnIDs;
        
        for (int j = 0; j < EXISTING_CAMPAIGN_MAPIDS_COL_COUNT; ++j)
        {
            columnIDs.push_back(NEW_CAMPAIGN_MAPIDS_CELL_VALUE);
        }
        
        existingMapIDs.push_back(columnIDs);
    }

    std::vector<Map::Map*> campaignMaps;
    campaignMaps.push_back(new Map::Map(5, 5));
    campaignMaps.push_back(new Map::Map(5, 5));
    campaignMaps.push_back(new Map::Map(5, 5));
    
    existingMapIDs[0][1] = campaignMaps[0]->GetMapID();
    existingMapIDs[1][1] = campaignMaps[1]->GetMapID();
    existingMapIDs[2][1] = campaignMaps[2]->GetMapID();
    
    CampaignMap currentMap;
    currentMap.mapID = existingMapIDs[1][1];
    currentMap.coorX = EXISTING_CAMPAIGN_CURRENT_X_COOR;
    currentMap.coorY = EXISTING_CAMPAIGN_CURRENT_Y_COOR;

    existingCampaignObject = new Campaign(99999, EXISTING_CAMPAIGN_MAPIDS_ROW_COUNT, EXISTING_CAMPAIGN_MAPIDS_COL_COUNT, existingMapIDs, currentMap, campaignMaps);
}

void TestCampaign::tearDown(void) {
    delete newCampaignObject;

    existingCampaignObject->GetMapIDs().clear();
    existingCampaignObject->GetMapsInCampaign().clear();

    delete existingCampaignObject;
}

void TestCampaign::TestCampaignConstructor(void) {
    std::vector<std::vector<int>> newCampaignMapIDs = newCampaignObject->GetMapIDs();
    CPPUNIT_ASSERT_EQUAL(NEW_CAMPAIGN_MAPIDS_ROW_COUNT, (int)newCampaignMapIDs.size());
    
    for (int i = 0; i < (int)newCampaignMapIDs.size(); ++i)
    {
        CPPUNIT_ASSERT_EQUAL(NEW_CAMPAIGN_MAPIDS_COL_COUNT, (int)newCampaignMapIDs.at(i).size());

        for (int j = 0; j < (int)newCampaignMapIDs[i].size(); j++)
        {
            CPPUNIT_ASSERT_EQUAL(NEW_CAMPAIGN_MAPIDS_CELL_VALUE, newCampaignMapIDs.at(i).at(j));
        }
    }

    campaign::CampaignMap newCampaignCurrentMap = newCampaignObject->GetCurrentMap();
    CPPUNIT_ASSERT_EQUAL(NEW_CAMPAIGN_MAPIDS_CELL_VALUE, newCampaignCurrentMap.mapID);
    CPPUNIT_ASSERT_EQUAL(NEW_CAMPAIGN_MAPIDS_CELL_VALUE, newCampaignCurrentMap.coorX);
    CPPUNIT_ASSERT_EQUAL(NEW_CAMPAIGN_MAPIDS_CELL_VALUE, newCampaignCurrentMap.coorY);

    CPPUNIT_ASSERT_EQUAL(0, (int)newCampaignObject->GetMapsInCampaign().size());
    
    std::vector<std::vector<int>> existingCampaignMapIDs = existingCampaignObject->GetMapIDs();
    CPPUNIT_ASSERT_EQUAL(EXISTING_CAMPAIGN_MAPIDS_ROW_COUNT, (int)existingCampaignMapIDs.size());
    
    for (int i = 0; i < (int)existingCampaignMapIDs.size(); ++i)
    {
        CPPUNIT_ASSERT_EQUAL(EXISTING_CAMPAIGN_MAPIDS_COL_COUNT, (int)existingCampaignMapIDs.at(i).size());

        for (int j = 0; j < (int)existingCampaignMapIDs.at(i).size(); j++)
        {
            std::vector<Map::Map*> mapsInCampaign = existingCampaignObject->GetMapsInCampaign();

            int mapIDAtCell = existingCampaignMapIDs.at(i).at(j);

            if (i == 0 && j == 1) {
                CPPUNIT_ASSERT_EQUAL(mapsInCampaign.at(0)->GetMapID(), mapIDAtCell);

                continue;
            }
            else if (i == 1 && j == 1) {
                CPPUNIT_ASSERT_EQUAL(mapsInCampaign.at(1)->GetMapID(), mapIDAtCell);

                continue;
            }
            else if (i == 2 && j == 1) {
                CPPUNIT_ASSERT_EQUAL(mapsInCampaign.at(2)->GetMapID(), mapIDAtCell);

                continue;
            }

            CPPUNIT_ASSERT_EQUAL(0, mapIDAtCell);
        }
    }

    campaign::CampaignMap existingCampaignCurrentMap = existingCampaignObject->GetCurrentMap();
    CPPUNIT_ASSERT_EQUAL(existingCampaignObject->GetMapsInCampaign().at(1)->GetMapID(), existingCampaignCurrentMap.mapID);
    CPPUNIT_ASSERT_EQUAL(EXISTING_CAMPAIGN_CURRENT_X_COOR, existingCampaignCurrentMap.coorX);
    CPPUNIT_ASSERT_EQUAL(EXISTING_CAMPAIGN_CURRENT_Y_COOR, existingCampaignCurrentMap.coorY);
    
    CPPUNIT_ASSERT_EQUAL(3, (int)existingCampaignObject->GetMapsInCampaign().size());
}

void TestCampaign::TestAddNewMap(void) {
    Map::Map* newMap1 = new Map::Map(5, 5);

    CPPUNIT_ASSERT_NO_THROW(existingCampaignObject->AddMapToCampaign(1, 2, *newMap1));
    CPPUNIT_ASSERT_EQUAL(newMap1->GetMapID(), existingCampaignObject->GetMapIDs().at(0).at(1));
    CPPUNIT_ASSERT_EQUAL(3, (int)existingCampaignObject->GetMapsInCampaign().size());

    Map::Map* newMap2 = new Map::Map(5, 5);

    CPPUNIT_ASSERT_NO_THROW(existingCampaignObject->AddMapToCampaign(3, 3, *newMap2));
    CPPUNIT_ASSERT_EQUAL(newMap2->GetMapID(), existingCampaignObject->GetMapIDs().at(2).at(2));
    CPPUNIT_ASSERT_EQUAL(4, (int)existingCampaignObject->GetMapsInCampaign().size());

    delete newMap1;
    delete newMap2;
}

void TestCampaign::TestGetMap(void) {
    std::ostringstream message;
    message << "Invalid coordiantes: " << EXISTING_CAMPAIGN_INVALID_X_COOR << "," << EXISTING_CAMPAIGN_INVALID_Y_COOR;
    CPPUNIT_ASSERT_THROW_MESSAGE(message.str(),
                                existingCampaignObject->GetMap(EXISTING_CAMPAIGN_INVALID_X_COOR, EXISTING_CAMPAIGN_INVALID_Y_COOR),
                                std::invalid_argument);

    int expectedMapID = existingCampaignObject->GetMapsInCampaign().at(1)->GetMapID();
    
    Map::Map* foundMap = existingCampaignObject->GetMap(EXISTING_CAMPAIGN_X_COOR, EXISTING_CAMPAIGN_Y_COOR);
    CPPUNIT_ASSERT_EQUAL(expectedMapID, foundMap->GetMapID());

    campaign::CampaignMap currentMap = existingCampaignObject->GetCurrentMap();
    CPPUNIT_ASSERT_EQUAL(expectedMapID, currentMap.mapID);
    CPPUNIT_ASSERT_EQUAL(EXISTING_CAMPAIGN_X_COOR, currentMap.coorX);
    CPPUNIT_ASSERT_EQUAL(EXISTING_CAMPAIGN_Y_COOR, currentMap.coorY);
}

void TestCampaign::TestSaveCampaign(void) {
    std::string currentPath = std::filesystem::current_path().string();

	std::ostringstream folderURI;
	folderURI << currentPath << SAVED_CAMPAIGNS_FOLDER_NAME;

	CPPUNIT_ASSERT_NO_THROW(campaign::SaveCampaigns(folderURI.str(), *newCampaignObject));

    std::ostringstream newCampaignFilePath;
    newCampaignFilePath << folderURI.str() << "\\Campaign" << newCampaignObject->GetCampaignID() << ".csv";

	struct stat newCampaignFileBuffer;
	CPPUNIT_ASSERT(stat(newCampaignFilePath.str().c_str(), &newCampaignFileBuffer) == 0);

    CPPUNIT_ASSERT_NO_THROW(campaign::SaveCampaigns(folderURI.str(), *existingCampaignObject));

    std::ostringstream existingCampaignFilePath;
    existingCampaignFilePath << folderURI.str() << "\\Campaign" << existingCampaignObject->GetCampaignID() << ".csv";

	struct stat existingCampaignFileBuffer;
	CPPUNIT_ASSERT(stat(existingCampaignFilePath.str().c_str(), &existingCampaignFileBuffer) == 0);
}

void TestCampaign::TestLoadCampaign(void) {
    std::ostringstream fileNotFoundMessage;
	fileNotFoundMessage << "Failed to open the file at: " << SAVED_CAMPAIGNS_INVALID_URI;
	CPPUNIT_ASSERT_THROW_MESSAGE(fileNotFoundMessage.str(), campaign::LoadCampaign(newCampaignObject->GetCampaignID(), SAVED_CAMPAIGNS_INVALID_URI), std::invalid_argument);

    std::string currentPath = std::filesystem::current_path().string();

    std::ostringstream folderURI;
	folderURI << currentPath << SAVED_CAMPAIGNS_FOLDER_NAME;

    campaign::CampaignRecord* testCampaignRecord = campaign::LoadCampaign(0, folderURI.str());

    CPPUNIT_ASSERT_EQUAL(0, testCampaignRecord->campaignID);
    CPPUNIT_ASSERT_EQUAL(EXISTING_CAMPAIGN_MAPIDS_ROW_COUNT, testCampaignRecord->numRows);
    CPPUNIT_ASSERT_EQUAL(EXISTING_CAMPAIGN_MAPIDS_COL_COUNT, testCampaignRecord->numCols);

    std::vector<std::vector<int>>* existingCampaignMapIDs = &testCampaignRecord->mapIDs;
    CPPUNIT_ASSERT_EQUAL(EXISTING_CAMPAIGN_MAPIDS_ROW_COUNT, (int)existingCampaignMapIDs->size());
    
    for (int i = 0; i < (int)existingCampaignMapIDs->size(); ++i)
    {
        CPPUNIT_ASSERT_EQUAL(EXISTING_CAMPAIGN_MAPIDS_COL_COUNT, (int)existingCampaignMapIDs->at(i).size());

        for (int j = 0; j < (int)existingCampaignMapIDs->at(i).size(); j++)
        {
            int mapIDAtCell = existingCampaignMapIDs->at(i).at(j);

            if (i == 0 && j == 1) {
                CPPUNIT_ASSERT_EQUAL(47, mapIDAtCell);

                continue;
            }
            else if (i == 1 && j == 1) {
                CPPUNIT_ASSERT_EQUAL(48, mapIDAtCell);

                continue;
            }
            else if (i == 2 && j == 1) {
                CPPUNIT_ASSERT_EQUAL(49, mapIDAtCell);

                continue;
            }

            CPPUNIT_ASSERT_EQUAL(0, mapIDAtCell);
        }
    }

    CPPUNIT_ASSERT_EQUAL(48, testCampaignRecord->currentMapID);
    CPPUNIT_ASSERT_EQUAL(2, testCampaignRecord->currentMapXCoor);
    CPPUNIT_ASSERT_EQUAL(2, testCampaignRecord->currentMapYCoor);
    CPPUNIT_ASSERT_EQUAL(3, (int)testCampaignRecord->mapsInCampaign.size());
}
