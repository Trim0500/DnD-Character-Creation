#include <algorithm>
#include <sstream>

#include "EmptyCell.h"
#include "game.h"

namespace {

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
        CreateObserverMessage("[Game/GameSetup] -- Fetching Campaign save data...\n");

        // Find campaign...

        CreateObserverMessage("[Game/GameSetup] -- Loading map data...\n");

        // Find generate maps...

        CreateObserverMessage("[Game/GameSetup] -- Loading characters...\n");

        // Find generate characters...

        // Set campaign memeber variables...

        CreateObserverMessage("[Game/GameSetup] -- Game setup complete! Ready to Play!\n");
    }

    Map::Map* Game::LoadMap(/* Door or ID */) {
        CreateObserverMessage("[Game/LoadMap] -- Door used, finding which map to bring up...\n");

        // Use door or ID to find map to load through the campaign member variable...

        CreateObserverMessage("[Game/LoadMap] -- Found the map the player is in!\n");

        return new Map::Map();
    }

    void Game::EndTurn(const std::string& _actionTaken, const int& _targetX, const int& _targetY) {
        CreateObserverMessage("[Game/EndTurn] -- A character ended their turn, need to update game data...\n");

        CampaignMap currentMapInCampaign = gameCampaign->GetCurrentMap();
        Map::Map* currentLoadedMap = gameCampaign->GetMap(currentMapInCampaign.coorX, currentMapInCampaign.coorY);

        if (_actionTaken == Character::EMPTY_CELL_ACTION) {
            currentLoadedMap->MoveCharacter(_targetX, _targetY, activeCharacter);
        }
        else if (_actionTaken == Character::ATTACK_CELL_ACTION) {
            std::vector<std::vector<Interactable::Interactable*>> mapGrid = currentLoadedMap->getGrid();
            Character::Character* target = static_cast<Character::Character*>(mapGrid[_targetX - 1][_targetY - 1]);
            bool targetDied = activeCharacter->AttemptAttack(target);
            if (targetDied) {
                charactersInMap.erase(std::remove(charactersInMap.begin(), charactersInMap.end(), target), charactersInMap.end());
                
                Interactable::Interactable* targetsItems = &target->Inventory();
                currentLoadedMap->setCell(_targetX - 1, _targetY - 1, targetsItems);
            }
        }

        CreateObserverMessage("[Game/EndTurn] -- Game campaign updates complete! Updating turn...\n");

        Character::Character* activeCharacterPointer = activeCharacter;
        std::vector<Character::Character*>::iterator currentActiveCharacter = std::find_if(charactersInMap.begin(),
                                                                                            charactersInMap.end(),
                                                                                            [activeCharacterPointer](Character::Character* character){ return character == activeCharacterPointer; });
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

        std::cout << "---------- Turn Ending Actions ----------" << std::endl;
        std::cout << "M. Move" << std::endl;

        auto attackAction = std::find_if(playerActions.begin(),
                                            playerActions.end(),
                                            [](CellActionInfo playerAction) { return playerAction.actionName == Character::ATTACK_CELL_ACTION; });
        if (attackAction != playerActions.end()) {
            std::cout << "A. Attack Character" << std::endl;
        }

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
        Character::Character* current_character_buffer = this->GetActiveCharacter();
        //set active character to player character
        this->SetActiveCharacter(t_playerCharacter);
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
            //Inspect item


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
                std::cout << "Moved from: (" << yOld << "," << xOld << ") -> (" << y << "," << x << ")" << std::endl;
            }
            else if (direction == "down") {
                currentMap->MoveCharacter(x+1, y, t_playerCharacter);
                currentMap->GetCharacterCoordinates(x, y, t_playerCharacter);
                std::cout << "Moved from: (" << yOld << "," << xOld << ") -> (" << y << "," << x << ")" << std::endl;

            }
            else if (direction == "left") {
                currentMap->MoveCharacter(x, y-1, t_playerCharacter);
                currentMap->GetCharacterCoordinates(x, y, t_playerCharacter);
                std::cout << "Moved from: (" << yOld << "," << xOld << ") -> (" << y << "," << x << ")" << std::endl;

            }
            else if (direction == "right") {
                currentMap->MoveCharacter(x, y+1, t_playerCharacter);
                currentMap->GetCharacterCoordinates(x, y, t_playerCharacter);
                std::cout << "Moved from: (" << xOld << "," << xOld << ") -> (" << y << "," << x << ")" << std::endl;
            }else{
                std::cout << "Invalid direction!" << std::endl;
            }
            
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
            break;
        }
        case 'E':
            std::cout << "Goodbye!" << std::endl;
            break;
        default:
            std::cout << "Unkown Action!" << std::endl;
            break;
        }
        this->SetActiveCharacter(current_character_buffer);
    }
}
