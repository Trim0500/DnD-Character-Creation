#include <algorithm>
#include <sstream>
#include <iterator>
#include <string>
#include <cctype>
#include <sys/stat.h>
#include <regex>

#include "game.h"
#include "..\Interactable\EmptyCell.h"
#include "..\Door\door.h"
#include "../Serialize/SerializeCharacter.h"
#include "../Builder/MapBuilder.h"

using namespace door;
using namespace serializeItem;
using namespace campaign;

namespace {
    std::vector<Item> FindItemsByIDInput(std::vector<int> _idInput, std::vector<Item> itemsToSearch) {
		std::vector<Item> result;

		for (int id : _idInput)
		{
			auto foundItem = std::find_if(itemsToSearch.begin(),
											itemsToSearch.end(),
											[id](Item item) { return item.GetItemId() == id; });
			if (foundItem != itemsToSearch.end()) {
				result.push_back((*foundItem));
			}
		}

		return result;
	}

    ItemContainer* FindCharacterInventory(const int& inventoryID, const std::vector<ItemContainer*>& containersToSearch) {
        auto foundInventory = std::find_if(containersToSearch.begin(),
                                            containersToSearch.end(),
                                            [inventoryID](ItemContainer* container) { return container->GetItemId() == inventoryID; });
        if (foundInventory != containersToSearch.end()) {
            return (*foundInventory);
        }
        else {
            return nullptr;
        }
    }

    void ProcessContainerAction(Item* _target, Character::Character* _playerCharacter, const bool& dropItems = false) {
        ItemContainer* containerTarget = static_cast<ItemContainer*>(_target);
        containerTarget->PrintItemVector();
        
        std::cout << "Enter a comma seperated list wo/spaces (ex. 1,2,3) or enter \'Back\' to exit." << std::endl;

        std::string containerSelection;
        std::cin >> containerSelection;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::remove_if(containerSelection.begin(),
                        containerSelection.end(),
                        [](unsigned char x) { return std::isspace(x); });

        std::transform(containerSelection.begin(),
                        containerSelection.end(),
                        containerSelection.begin(),
                        [](unsigned char c) { return std::tolower(c); });
        if (containerSelection != "back") {
            std::vector<Item> containerItems = containerTarget->GetAllItems();

            std::stringstream lineStream(containerSelection);

            std::vector<Item*> segmentList;

            std::string segment = "";
            while (std::getline(lineStream, segment, ',')) {
                int indexForItem = std::stoi(segment) - 1;
                segmentList.push_back(&containerItems[indexForItem]);
            }
            
            if (!dropItems) {
                try {
                    _playerCharacter->TakeItems(containerTarget, segmentList, _playerCharacter->Inventory().GetItemId());

                    std::cout << _playerCharacter->Name() << " added items to their inventory!" << std::endl;
                }
                catch (std::invalid_argument exc) {
                    std::cout << exc.what() << std::endl;
                }
                catch (std::overflow_error exc) {
                    std::cout << "Can't add the items to the inventory! Try changing your selection!" << std::endl;
                }
            }
            else {
                try {
                    _playerCharacter->DropItems(segmentList, _target->GetItemId());

                    std::cout << _playerCharacter->Name() << " dropped items from their inventory!" << std::endl;
                }
                catch (std::invalid_argument exc) {
                    std::cout << exc.what() << std::endl;
                }
            }
        }
    }

    void ProcessUserItemAction(Map::Map* _currentMap,
                                Character::Character* _playerCharacter,
                                const int& _playerX,
                                const int& _playerY,
                                const bool& dropItems = false) {
        std::vector<std::vector<Interactable::Interactable*>> mapGrid = _currentMap->getGrid();

        std::vector<CellActionInfo> playerActions = _playerCharacter->GetActionStrategy()->UseMovementStrategy(mapGrid, _playerX + 1, _playerY + 1);

        auto pickUpAction = std::find_if(playerActions.begin(),
                                            playerActions.end(),
                                            [](CellActionInfo playerAction) { return playerAction.actionName == Character::PICKUP_CELL_ACTION; });
        Item* target = static_cast<Item*>(mapGrid[(*pickUpAction).row - 1][(*pickUpAction).col - 1]);
        if (dynamic_cast<ItemContainer*>(target)) {
            ProcessContainerAction(target, _playerCharacter, dropItems);
        }
        else {
            std::cout << "Item details: " << target->GetItemName() << std::endl;
            std::cout << "Pickup item? (y/Y or n/N)" << std::endl;
            char pickUpSelection = ' ';
            std::cin.get(pickUpSelection);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if ((char)tolower(pickUpSelection) == 'y') {
                ItemContainer* playerInventory = &_playerCharacter->Inventory();
                int addResult = playerInventory->AddNewItem(target);
                if (addResult == -1) {
                    std::cout << "Can't add the item to the inventory! Try dropping an item to free up space!" << std::endl;
                }
                else {
                    std::cout << _playerCharacter->Name() << " added " << target->GetItemName() << " to their inventory!" << std::endl;

                    _currentMap->setEmpty((*pickUpAction).row - 1, (*pickUpAction).col - 1);
                }
            }
        }
    }
}

namespace game
{
    void Game::Notify() {
        for (int i = 0; i < (int)observers.size(); i++)
        {
            observers[i]->update(observerMessage);
        }
    }

    void Game::CreateObserverMessage(std::string _message = "Empty") {
        observerMessage = _message;
        
        Notify();
    }

    void Game::GameSetup(std::filesystem::path* _campaignDir, Observer* _gameLogger) {
        CampaignRecord* campaignRecord = LoadCampaign(_campaignDir->string());
        
        _campaignDir->remove_filename();

        CreateObserverMessage("[Game/GameSetup] -- Loading items...");

        std::filesystem::path itemsPath = *_campaignDir / "Items" / "items.csv";
        std::vector<Item*> itemsInCampaign = LoadItems(itemsPath.string());

        std::filesystem::path itemContainersPath = *_campaignDir / "Item Containers" / "item_containers.csv";
        std::vector<ItemContainerRecord*> containersRecords = LoadItemContainerRecords(itemContainersPath.string());

        std::vector<Item> copyItems;
        for (int i = 0; i < (int)itemsInCampaign.size(); i++)
        {
            copyItems.push_back(*itemsInCampaign[i]);
        }

        std::vector<ItemContainer*> containersInCampaign;
        for (int i = 0; i < (int)containersRecords.size(); i++)
        {
            std::vector<Item> containerItems = FindItemsByIDInput(containersRecords[i]->itemIDs, copyItems);
            ItemContainer* savedContainer = new ItemContainer(containersRecords[i]->containerId,
                                                                containersRecords[i]->itemName,
                                                                0,
                                                                containersRecords[i]->itemtype,
                                                                item::CharacterStats::NA,
                                                                containersRecords[i]->weight,
                                                                containersRecords[i]->capacity,
                                                                containerItems);
            containersInCampaign.push_back(savedContainer);
        }

        CreateObserverMessage("[Game/GameSetup] -- Loading characters...");

        std::filesystem::path charactersPath = *_campaignDir / "Characters";
        std::vector<serializecharacter::CharacterRecord> characterRecords = serializecharacter::LoadAllCharacters(charactersPath.string());
        
        std::vector<Character::Character*> charactersInCampaign;
        for (int i = 0; i < (int)characterRecords.size(); i++)
        {
            Character::Character* character;
            ItemContainer* characterInventory = FindCharacterInventory(characterRecords[i].inventory_container_id, containersInCampaign);
            if (characterInventory != nullptr) {
                character = new Character::Character(characterRecords[i], *characterInventory);
            }
            else {
                character = new Character::Character(characterRecords[i], ItemContainer("Inventory", item::ItemType::Inventory, 30.0));
            }

            character->Attach(_gameLogger);

            charactersInCampaign.push_back(character);
        }

        CreateObserverMessage("[Game/GameSetup] -- Loading map data...");
        
        std::filesystem::path doorsPath = *_campaignDir / "Doors" / "doors.csv";
        std::vector<Door*> doorsInCampaign = LoadDoors(doorsPath.string());

        std::filesystem::path mapsPath = *_campaignDir / "Maps";
        std::string path(mapsPath.string());

        std::string ext(".csv");

        std::vector<Map::Map*> mapsInCampaign;

        CampaignMap currentMap;

        for (auto &file : std::filesystem::directory_iterator(path))
        {
            if (file.path().extension() == ext)
            {
                std::string filePath = file.path().string();
                Map::Map *loadedMap = MapBuilder::MapBuilder::LoadMap(filePath);

                std::vector<std::vector<Interactable::Interactable*>> grid = loadedMap->getGrid();

                for (int i = 0; i < (int)grid.size(); i++)
                {
                    for (int j = 0; j < (int)grid[i].size(); j++)
                    {
                        if (dynamic_cast<Door*>(grid[i][j])) {
                            int doorID = static_cast<Door*>(grid[i][j])->GetDoorID();
                            auto foundDoor = std::find_if(doorsInCampaign.begin(),
                                                            doorsInCampaign.end(),
                                                            [doorID](Door* door) { return door->GetDoorID() == doorID;});
                            if (foundDoor != doorsInCampaign.end()) {
                                grid[i][j] = (*foundDoor);
                            }
                        }
                        else if (dynamic_cast<Character::Character*>(grid[i][j])) {
                            int characterID = static_cast<Character::Character*>(grid[i][j])->ID();
                            auto foundCharacter = std::find_if(charactersInCampaign.begin(),
                                                                charactersInCampaign.end(),
                                                                [characterID](Character::Character* character) { return character->ID() == characterID;});
                            if (foundCharacter != charactersInCampaign.end()) {
                                grid[i][j] = (*foundCharacter);
                                if (static_cast<Character::Character*>(grid[i][j])->GetIsPlayerControlled()) {
                                    currentMap.mapID = loadedMap->GetMapID();

                                    activeCharacter = (*foundCharacter);

                                    charactersInMap.push_back((*foundCharacter));
                                }
                            }
                        }
                        else if (dynamic_cast<ItemContainer*>(grid[i][j])) {
                            int containerID = static_cast<ItemContainer*>(grid[i][j])->GetItemId();
                            auto foundContainer = std::find_if(containersInCampaign.begin(),
                                                                containersInCampaign.end(),
                                                                [containerID](ItemContainer* container) { return container->GetItemId() == containerID;});
                            if (foundContainer != containersInCampaign.end()) {
                                grid[i][j] = (*foundContainer);
                            }
                        }
                        else if (dynamic_cast<Item*>(grid[i][j])) {
                            int itemID = static_cast<Item*>(grid[i][j])->GetItemId();
                            auto foundItem = std::find_if(itemsInCampaign.begin(),
                                                            itemsInCampaign.end(),
                                                            [itemID](Item* item) { return item->GetItemId() == itemID;});
                            if (foundItem != itemsInCampaign.end()) {
                                grid[i][j] = (*foundItem);
                            }
                        }
                    }
                }

                loadedMap->setGrid(grid);

                mapsInCampaign.push_back(loadedMap);
            }
        }

        CreateObserverMessage("[Game/GameSetup] -- Fetching Campaign save data...");

        std::vector<Map::Map*> campaignMaps;
        
        for (int i = 0; i < (int)campaignRecord->mapsInCampaign.size(); i++)
        {
            int mapID = campaignRecord->mapsInCampaign[i];
            auto foundMap = std::find_if(mapsInCampaign.begin(),
                                            mapsInCampaign.end(),
                                            [mapID](Map::Map* map) { return map->GetMapID() == mapID;});
            if (foundMap != mapsInCampaign.end()) {
                campaignMaps.push_back((*foundMap));
                if (currentMap.mapID == (*foundMap)->GetMapID()) {
                    int mapIDToFind = currentMap.mapID;
                    for (int i = 0; i < (int)campaignRecord->numRows; i++)
                    {
                        
                        auto foundMapID = std::find_if(campaignRecord->mapIDs[i].begin(),
                                                        campaignRecord->mapIDs[i].end(),
                                                        [mapIDToFind](int mapID) { return mapID == mapIDToFind;});
                        if (foundMapID != campaignRecord->mapIDs[i].end()) {
                            currentMap.coorX = i + 1;
                            currentMap.coorY = (foundMapID - campaignRecord->mapIDs[i].begin()) + 1;

                            break;
                        }
                    }

                    std::vector<std::vector<Interactable::Interactable*>> grid = (*foundMap)->getGrid();

                    for (int i = 0; i < (int)grid.size(); i++)
                    {
                        for (int j = 0; j < (int)grid[i].size(); j++)
                        {
                            if (dynamic_cast<Character::Character*>(grid[i][j])) {
                                if (static_cast<Character::Character*>(grid[i][j])->GetIsPlayerControlled()) {
                                    continue;
                                }
                                
                                charactersInMap.push_back(static_cast<Character::Character*>(grid[i][j]));
                            }
                        }
                    }
                }
            }
        }

        gameCampaign = new Campaign(campaignRecord->campaignID, campaignRecord->numRows, campaignRecord->numCols, campaignRecord->mapIDs, currentMap, campaignMaps);

        CreateObserverMessage("[Game/GameSetup] -- Game setup complete! Ready to Play!");
    }

    Map::Map* Game::LoadMap(/* Door or ID */) {
        CreateObserverMessage("[Game/LoadMap] -- Door used, finding which map to bring up...");

        // Use door or ID to find map to load through the campaign member variable...

        CreateObserverMessage("[Game/LoadMap] -- Found the map the player is in!");

        return new Map::Map();
    }

    void Game::EndTurn(const std::string& _actionTaken, const int& _targetX, const int& _targetY) {
        CreateObserverMessage("[Game/EndTurn] -- A character ended their turn, need to update game data...");

        CampaignMap currentMapInCampaign = gameCampaign->GetCurrentMap();
        Map::Map* currentLoadedMap = gameCampaign->GetMap(currentMapInCampaign.coorX, currentMapInCampaign.coorY);

        if (_actionTaken == Character::EMPTY_CELL_ACTION) {
            currentLoadedMap->MoveCharacter(_targetX, _targetY, activeCharacter);
        }
        else if (_actionTaken == Character::ATTACK_CELL_ACTION) {
            std::vector<std::vector<Interactable::Interactable*>> mapGrid = currentLoadedMap->getGrid();
            Character::Character* target = static_cast<Character::Character*>(mapGrid[_targetX - 1][_targetY - 1]);
            bool targetDied = activeCharacter->AttemptAttack(target);

            std::ostringstream attackUpdateMessage;
            attackUpdateMessage << "Attack results: " << target->Name() << " now at " << target->Hit_Points() << std::endl;
            std::cout << attackUpdateMessage.str();

            if (targetDied) {
                charactersInMap.erase(std::remove(charactersInMap.begin(), charactersInMap.end(), target), charactersInMap.end());
                
                Interactable::Interactable* targetsItems = &target->Inventory();
                currentLoadedMap->setCell(_targetX - 1, _targetY - 1, targetsItems);

                std::ostringstream killUpdateMessage;
                killUpdateMessage << target->Name() << " killed! Inventory dropped. " << std::endl;
                std::cout << killUpdateMessage.str();
            }
        }

        CreateObserverMessage("[Game/EndTurn] -- Game campaign updates complete! Updating turn...");

        Character::Character* activeCharacterPointer = activeCharacter;
        std::vector<Character::Character*>::iterator currentActiveCharacter = std::find_if(charactersInMap.begin(),
                                                                                            charactersInMap.end(),
                                                                                            [activeCharacterPointer](Character::Character* character){ return character == activeCharacterPointer; });
        currentActiveCharacter = std::next(currentActiveCharacter, 1);
        if (currentActiveCharacter == charactersInMap.end()) {
            currentActiveCharacter = charactersInMap.begin();
        }

        activeCharacter = (*currentActiveCharacter);
    }

    void Game::PrintActionMenu(Character::Character* _player)
    {
        CampaignMap currentMapInCampaign = gameCampaign->GetCurrentMap();
        Map::Map* currnetMapGrid = gameCampaign->GetMap(currentMapInCampaign.coorX, currentMapInCampaign.coorY);

        int playerX, playerY;
        currnetMapGrid->GetCharacterCoordinates(playerX, playerY, _player);

        std::vector<CellActionInfo> playerActions = _player->GetActionStrategy()->UseMovementStrategy(currnetMapGrid->getGrid(), playerX + 1, playerY + 1);

        std::cout << std::endl;
        std::cout << "---------- Action Menu ----------" << std::endl;
        std::cout << "(Select number and press 'Enter')" << std::endl;
        std::cout << "1. Print map" << std::endl;
        std::cout << "2. Print Player character sheet" << std::endl;
        std::cout << "3. Print List of Characters" << std::endl;
        std::cout << "4. Print Player Coordinates" << std::endl;

        auto pickUpAction = std::find_if(playerActions.begin(),
                                            playerActions.end(),
                                            [](CellActionInfo playerAction) { return playerAction.actionName == Character::PICKUP_CELL_ACTION; });
        if (pickUpAction != playerActions.end()) {
            std::cout << "I. Inspect Item" << std::endl;
        }

        auto doorAction = std::find_if(playerActions.begin(),
                                            playerActions.end(),
                                            [](CellActionInfo playerAction) { return playerAction.actionName == Character::DOOR_CELL_ACTION; });
        if (doorAction != playerActions.end()) {
            std::cout << "W. Use door" << std::endl;
        }
        
        std::cout << "P. Equip item" << std::endl;
        std::cout << "K. Unequip item" << std::endl;

        if (_player->Inventory().GetAllItems().size() != 0) {
            std::cout << "R. Drop Items" << std::endl;
        }

        std::cout << "---------- Turn Ending Actions ----------" << std::endl;
        std::cout << "M. Move" << std::endl;

        auto attackAction = std::find_if(playerActions.begin(),
                                            playerActions.end(),
                                            [](CellActionInfo playerAction) { return playerAction.actionName == Character::ATTACK_CELL_ACTION; });
        if (attackAction != playerActions.end()) {
            std::cout << "A. Attack Character" << std::endl;
        }

        std::cout << "D. Do Nothing" << std::endl;

        std::cout << "---------- Systems Actions ----------" << std::endl;
        std::cout << "Press 'E' and 'Enter' to exit" << std::endl;

    }

    void Game::GetUserSelection(char& t_selection)
    {
        std::cin.get(t_selection);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }

    void Game::ProcessUserAction(const char& t_selection, Character::Character* t_playerCharacter)
    {
        //hold current character
        //Character::Character* current_character_buffer = this->GetActiveCharacter();
        //set active character to player character
        //this->SetActiveCharacter(t_playerCharacter);
        //get current map
        int x, y;
        CampaignMap currentMapInCampaign = gameCampaign->GetCurrentMap();
        Map::Map* currentMap = gameCampaign->GetMap(currentMapInCampaign.coorX, currentMapInCampaign.coorY);
        currentMap->GetCharacterCoordinates(x, y, t_playerCharacter);
        std::string direction;

        switch(t_selection)
        {
        case '1':
            //Print first map in campaign
            this->GetGameCampaign()->GetMapsInCampaign()[0]->printMap();
            break;
        case '2':
            //Print player Character sheet
            t_playerCharacter->Print_Character_Sheet();
            break;
        case '4':
            //Print player character location
            std::cout << "Player Location: " << y << "," << x << std::endl;
            break;

        case 'I':
        {
            ProcessUserItemAction(currentMap, t_playerCharacter, x, y);

            CreateObserverMessage("[Game/ProcessUserAction] -- Player interacted with items!");

            break;
        }
        case 'W':
        {
            std::vector<CellActionInfo> playerActions = activeCharacter->GetActionStrategy()->UseMovementStrategy(currentMap->getGrid(), x + 1, y + 1);
            currentMap->setEmpty(x, y);

            auto doorAction = std::find_if(playerActions.begin(),
                                            playerActions.end(),
                                            [](CellActionInfo playerAction) { return playerAction.actionName == Character::DOOR_CELL_ACTION; });
            Door* doorToUse = static_cast<Door*>(currentMap->getGrid().at((*doorAction).row - 1).at((*doorAction).col - 1));
            
            int currentMapID = gameCampaign->GetCurrentMap().mapID;
            DoorDestinationInfo destinationInfo = doorToUse->UseDoor(currentMapID);
            Map::Map* mapToLoad = gameCampaign->GetMap(destinationInfo.mapLocationX, destinationInfo.mapLocationY);
            mapToLoad->setCharacter(destinationInfo.destinationX - 1, destinationInfo.destinationY - 1, t_playerCharacter);

            std::vector<std::vector<Interactable::Interactable*>> newMapGrid = mapToLoad->getGrid();

            std::vector<Character::Character*> charactersInNewMap;
            for (int i = 0; i < (int)newMapGrid.size(); i++)
            {
                auto valueAtCell = std::find_if(newMapGrid[i].begin(),
                                                newMapGrid[i].end(),
                                                [](Interactable::Interactable* cell) { return dynamic_cast<Character::Character*>(cell); });
                if (valueAtCell != newMapGrid[i].end()) {
                    charactersInNewMap.push_back(static_cast<Character::Character*>((*valueAtCell)));

                    while (valueAtCell != newMapGrid[i].end())
                    {
                        valueAtCell = std::find_if(valueAtCell + 1,
                                                    newMapGrid[i].end(),
                                                    [](Interactable::Interactable* cell) { return dynamic_cast<Character::Character*>(cell); });

                        if (valueAtCell != newMapGrid[i].end()) {
                            charactersInNewMap.push_back(static_cast<Character::Character*>((*valueAtCell)));
                        }
                    }
                }
            }

            charactersInMap = charactersInNewMap;

            CreateObserverMessage("[Game/ProcessUserAction] -- Player used a door!");
            
            break;
        }
        case 'P': {
            //Equip item
            if (t_playerCharacter->Inventory().GetAllItems().size() <= 0) {
                std::cout << "No items in inventory to equip!" << std::endl;
                return;
            }
            std::vector<item::Item*> inventory;
            std::cout << std::right << std::setw(63) << "INVENTORY" << std::endl;
            std::cout << std::right << std::setw(35) << "Name" << " | " << std::left << std::setw(35) << "Type"
                << " | " << std::left << std::setw(35) << "Enchantment" << std::endl;
            std::cout << std::string(100, '-') << std::endl;
            int count = 0;
            for (int i{ 0 }; i<t_playerCharacter->Inventory().GetAllItems().size(); i++) {
                std::cout << count << ". ";
                std::cout << std::right << std::setw(35) << t_playerCharacter->Inventory().GetAllItems().at(i).GetItemName() << " | "
                    << std::left << std::setw(35) << t_playerCharacter->Get_Item_Type_String(t_playerCharacter->Inventory().GetAllItems().at(i).GetItemType()) << " | ";
                if (t_playerCharacter->Inventory().GetAllItems().at(i).GetEnchantmentBonus() > 0) {
                    std::cout << "+";
                }
                std::cout << t_playerCharacter->Inventory().GetAllItems().at(i).GetEnchantmentBonus() << " "
                    << t_playerCharacter->Get_Abilities_String(Character::item_stat_TO_character_stat.at(t_playerCharacter->Inventory().GetAllItems().at(i).GetEnchantmentType())) << std::endl;
                count++;
            }
            std::cout << "Equip item number :";
            std::string item_number_s;
            int item_number_i;
            std::getline(std::cin, item_number_s);
            item_number_i = std::stoi(item_number_s);
            if (item_number_i >= 0 && item_number_i < count) {
                t_playerCharacter->Equip_Item_Decorator(&t_playerCharacter->Inventory().GetAllItems().at(item_number_i));
                std::cout << "Item equppied!" << std::endl;
            }
            else{
                std::cout << "Could not equip item!" << std::endl;
            }

            CreateObserverMessage("[Game/ProcessUserAction] -- Player equipped items!");

            break;
        }
        case 'K': {
            //unequip item
            if (t_playerCharacter->GetWornItems()->GetDecoratorList().size() <= 0) {
                std::cout << "No items in inventory to equip!" << std::endl;
                return;
            }
            std::vector<item::Item*> equipped_items;
            item::Item* item;
            std::cout << std::right << std::setw(65) << "EQUIPPED ITEMS" << std::endl;
            std::cout << std::right << std::setw(35) << "Equipment slot" << " | " << std::left << std::setw(35) << " Name (ID)"
                << " | " << std::left << std::setw(35) << "Enchantment" << std::endl;
            std::cout << std::string(100, '-') << std::endl;
            int count = 0;
            for (int i{ 0 }; i < t_playerCharacter->GetWornItems()->GetDecoratorList().size(); i++) {
                item = dynamic_cast<item::Item*>(t_playerCharacter->GetWornItems()->GetDecoratorList().at(i));
                equipped_items.push_back(item);
                std::cout << count << ". ";
                std::cout << std::right << std::setw(35) << item->GetItemName() << " | "
                    << std::left << std::setw(35) << item->GetItemType() << " | ";
                if (item->GetEnchantmentBonus() > 0) {
                    std::cout << "+";
                }
                std::cout << item->GetEnchantmentBonus() << " "
                    << t_playerCharacter->Get_Abilities_String(Character::item_stat_TO_character_stat.at(item->GetEnchantmentType())) << std::endl;
                count++;
            }
            std::cout << "unequip item number :";
            std::string item_number_s;
            int item_number_i;
            std::getline(std::cin, item_number_s);
            item_number_i = std::stoi(item_number_s);
            if (item_number_i >= 0 && item_number_i < count) {
                t_playerCharacter->Unequip_Item_Decorator(equipped_items.at(item_number_i));
                std::cout << "Item unequipped!" << std::endl;
            }
            else {
                std::cout << "Could not unequip item!" << std::endl;
            }

            CreateObserverMessage("[Game/ProcessUserAction] -- Player unequipped items!");

            break;
        }
        case 'R':
            ProcessContainerAction(&t_playerCharacter->Inventory(),
                                    t_playerCharacter, true);

            CreateObserverMessage("[Game/ProcessUserAction] -- Player dropped items!");

            break;
        case 'M':
            int xOld, yOld;
            xOld = x;
            yOld = y;

            x++;
            y++;
            //Move
            std::cout << "Select Direction: up, down, left, right";
            std::getline(std::cin, direction);
            
            if (direction == "up") {
                currentMap->MoveCharacter(x-1, y, t_playerCharacter);
                currentMap->GetCharacterCoordinates(x, y, t_playerCharacter);
                std::cout << "Moved from: (" << xOld << "," << yOld << ") -> (" << x << "," << y << ")" << std::endl;
            }
            else if (direction == "down") {
                currentMap->MoveCharacter(x+1, y, t_playerCharacter);
                currentMap->GetCharacterCoordinates(x, y, t_playerCharacter);
                std::cout << "Moved from: (" << xOld << "," << yOld << ") -> (" << x << "," << y << ")" << std::endl;

            }
            else if (direction == "left") {
                currentMap->MoveCharacter(x, y-1, t_playerCharacter);
                currentMap->GetCharacterCoordinates(x, y, t_playerCharacter);
                std::cout << "Moved from: (" << xOld << "," << yOld << ") -> (" << x << "," << y << ")" << std::endl;

            }
            else if (direction == "right") {
                currentMap->MoveCharacter(x, y+1, t_playerCharacter);
                currentMap->GetCharacterCoordinates(x, y, t_playerCharacter);
                std::cout << "Moved from: (" << xOld << "," << yOld << ") -> (" << x << "," << y << ")" << std::endl;
            }else{
                std::cout << "Invalid direction!" << std::endl;
            }

            CreateObserverMessage("[Game/ProcessUserAction] -- Player moved!");
            
            break;
        case 'A':
        {
            std::vector<std::vector<Interactable::Interactable*>> mapGrid = currentMap->getGrid();

            std::vector<CellActionInfo> playerActions = t_playerCharacter->GetActionStrategy()->UseMovementStrategy(mapGrid, x + 1, y + 1);

            auto attackAction = std::find_if(playerActions.begin(),
                                                playerActions.end(),
                                                [](CellActionInfo playerAction) { return playerAction.actionName == Character::ATTACK_CELL_ACTION; });

            Character::Character* target = static_cast<Character::Character*>(mapGrid[(*attackAction).row - 1][(*attackAction).col - 1]);
            bool targetDied = t_playerCharacter->AttemptAttack(target);

            std::ostringstream attackUpdateMessage;
            attackUpdateMessage << "Attack results: " << target->Name() << " now at " << target->Hit_Points() << std::endl;
            std::cout << attackUpdateMessage.str();

            if (targetDied) {
                charactersInMap.erase(std::remove(charactersInMap.begin(), charactersInMap.end(), target), charactersInMap.end());

                Interactable::Interactable* targetsItems = &target->Inventory();
                currentMap->setCell((*attackAction).row - 1, (*attackAction).col - 1, targetsItems);

                std::ostringstream killUpdateMessage;
                killUpdateMessage << target->Name() << " killed! Inventory dropped. " << std::endl;
                std::cout << killUpdateMessage.str();
            }

            CreateObserverMessage("[Game/ProcessUserAction] -- Player attacked an enemy!");

            break;
        }
        case 'E':
            std::cout << "Goodbye!" << std::endl;

            CreateObserverMessage("[Game/ProcessUserAction] -- User exited the game session!");

            break;
        default:
            std::cout << "Unkown Action!" << std::endl;
            break;
        }

        if (t_selection == 'M' || t_selection == 'A' || t_selection == 'D') {
            Character::Character* activeCharacterPointer = activeCharacter;
            std::vector<Character::Character*>::iterator currentActiveCharacter = std::find_if(charactersInMap.begin(),
                                                                                                charactersInMap.end(),
                                                                                                [activeCharacterPointer](Character::Character* character){ return character == activeCharacterPointer; });
            currentActiveCharacter = std::next(currentActiveCharacter, 1);
            if (currentActiveCharacter == charactersInMap.end()) {
                currentActiveCharacter = charactersInMap.begin();
            }

            activeCharacter = (*currentActiveCharacter);

            CreateObserverMessage("[Game/ProcessUserAction] -- Player choose a turn ending action! NPC will move next!");
        }

        //this->SetActiveCharacter(current_character_buffer);
    }
}
