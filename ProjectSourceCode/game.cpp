#include <algorithm>
#include <sstream>
#include <iterator>
#include <string>
#include <cctype>

#include "EmptyCell.h"
#include "game.h"

namespace {
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

    void Game::GameSetup(const std::string& _saveFileDir) {
        CreateObserverMessage("[Game/GameSetup] -- Fetching Campaign save data...");

        // Find campaign...

        CreateObserverMessage("[Game/GameSetup] -- Loading map data...");

        // Find generate maps...

        CreateObserverMessage("[Game/GameSetup] -- Loading characters...");

        // Find generate characters...

        // Set campaign memeber variables...

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
        Map::Map* currnetMapGrid;
        currnetMapGrid = gameCampaign->GetMapsInCampaign().at(0);

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
        Map::Map* currentMap = GetGameCampaign()->GetMapsInCampaign()[0];
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
            this->GetActiveCharacter()->Print_Character_Sheet();
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
