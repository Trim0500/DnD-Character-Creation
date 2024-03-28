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

    void Game::EndTurn(const Map::Map&) {
        CreateObserverMessage("[Game/EndTurn] -- A character ended their turn, need to update game data...");

        // Look through each cell to update the game's campaign member variable...

        CreateObserverMessage("[Game/EndTurn] -- Map updates complete! moving on to characters...");

        // Use the map's cells to identify characters and update to game's campaign member variable

        CreateObserverMessage("[Game/EndTurn] -- Character updates complete! Updating turn...");

        // Update turn info...
    }
}
