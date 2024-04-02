#include <algorithm>

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
}
