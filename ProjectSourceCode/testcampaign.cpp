/*!
* \file testcampaign.cpp
* \brief Test implementation for Campaign
*/

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

    existingCampaignObject = new Campaign(existingMapIDs, currentMap, campaignMaps);
}

void TestCampaign::tearDown(void) {
    delete newCampaignObject;

    existingCampaignObject->GetMapIDs()->clear();
    existingCampaignObject->GetMapsInCampaign()->clear();

    delete existingCampaignObject;
}

void TestCampaign::TestCampaignConstructor(void) {
    std::vector<std::vector<int>>* newCampaignMapIDs = newCampaignObject->GetMapIDs();
    CPPUNIT_ASSERT_EQUAL(NEW_CAMPAIGN_MAPIDS_ROW_COUNT, (int)newCampaignMapIDs->size());
    
    for (int i = 0; i < (int)newCampaignMapIDs->size(); ++i)
    {
        CPPUNIT_ASSERT_EQUAL(NEW_CAMPAIGN_MAPIDS_COL_COUNT, (int)newCampaignMapIDs->at(i).size());

        for (int j = 0; j < (int)newCampaignMapIDs[i].size(); j++)
        {
            CPPUNIT_ASSERT_EQUAL(NEW_CAMPAIGN_MAPIDS_CELL_VALUE, newCampaignMapIDs->at(i).at(j));
        }
    }
    
    std::vector<std::vector<int>>* existingCampaignMapIDs = existingCampaignObject->GetMapIDs();
    CPPUNIT_ASSERT_EQUAL(EXISTING_CAMPAIGN_MAPIDS_ROW_COUNT, (int)existingCampaignMapIDs->size());
    
    for (int i = 0; i < (int)existingCampaignMapIDs->size(); ++i)
    {
        CPPUNIT_ASSERT_EQUAL(EXISTING_CAMPAIGN_MAPIDS_COL_COUNT, (int)existingCampaignMapIDs->at(i).size());

        for (int j = 0; j < (int)existingCampaignMapIDs->at(i).size(); j++)
        {
            std::vector<Map::Map*>* mapsInCampaign = existingCampaignObject->GetMapsInCampaign();

            int mapIDAtCell = existingCampaignMapIDs->at(i).at(j);

            if (i == 0 && j == 1) {
                CPPUNIT_ASSERT_EQUAL(mapsInCampaign->at(0)->GetMapID(), mapIDAtCell);

                continue;
            }
            else if (i == 1 && j == 1) {
                CPPUNIT_ASSERT_EQUAL(mapsInCampaign->at(1)->GetMapID(), mapIDAtCell);

                continue;
            }
            else if (i == 2 && j == 1) {
                CPPUNIT_ASSERT_EQUAL(mapsInCampaign->at(2)->GetMapID(), mapIDAtCell);

                continue;
            }

            CPPUNIT_ASSERT_EQUAL(0, mapIDAtCell);
        }
    }

    CampaignMap* existingCampaignCurrentMap = existingCampaignObject->GetCurrentMap();
    CPPUNIT_ASSERT_EQUAL(existingCampaignObject->GetMapsInCampaign()->at(1)->GetMapID(), existingCampaignCurrentMap->mapID);
    CPPUNIT_ASSERT_EQUAL(EXISTING_CAMPAIGN_CURRENT_X_COOR, existingCampaignCurrentMap->coorX);
    CPPUNIT_ASSERT_EQUAL(EXISTING_CAMPAIGN_CURRENT_Y_COOR, existingCampaignCurrentMap->coorY);
    
    CPPUNIT_ASSERT_EQUAL(3, (int)existingCampaignObject->GetMapsInCampaign()->size());
}

void TestCampaign::TestGetMap(void) {
    std::ostringstream message;
    message << "Invalid coordiantes: " << EXISTING_CAMPAIGN_INVALID_X_COOR << "," << EXISTING_CAMPAIGN_INVALID_Y_COOR;
    CPPUNIT_ASSERT_THROW_MESSAGE(message.str(),
                                existingCampaignObject->GetMap(EXISTING_CAMPAIGN_INVALID_X_COOR, EXISTING_CAMPAIGN_INVALID_Y_COOR),
                                std::invalid_argument);

    int expectedMapID = existingCampaignObject->GetMapsInCampaign()->at(1)->GetMapID();
    
    Map::Map* foundMap = existingCampaignObject->GetMap(EXISTING_CAMPAIGN_X_COOR, EXISTING_CAMPAIGN_Y_COOR);
    CPPUNIT_ASSERT_EQUAL(expectedMapID, foundMap->GetMapID());

    CampaignMap* currentMap = existingCampaignObject->GetCurrentMap();
    CPPUNIT_ASSERT_EQUAL(expectedMapID, currentMap->mapID);
    CPPUNIT_ASSERT_EQUAL(EXISTING_CAMPAIGN_X_COOR, currentMap->coorX);
    CPPUNIT_ASSERT_EQUAL(EXISTING_CAMPAIGN_Y_COOR, currentMap->coorY);
}
