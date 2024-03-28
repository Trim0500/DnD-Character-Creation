#pragma once

#include <vector>
#include <string>

#include "Observable.h"
#include "campaign.h"

using namespace observable;
using namespace campaign;

namespace game {
    class Game : public Observable {
        public:
            Game(){};

            virtual ~Game(){};

            void Attach (Observer* _observer) override { observers.push_back(_observer); };

            void Detach (Observer* _observer) override { observers.erase(std::remove(observers.begin(), observers.end(), _observer), observers.end()); };

            void Notify() override;

            void CreateObserverMessage(std::string);

            // Load in a save file likely and update campaign member(?)
            void GameSetup(const std::string&);

            // Good candidate to incorporate doors (pass a reference to the object just an ID to know what map to load from campaign member)
            Map::Map* LoadMap(/* Door or ID */);

            // Essentially use this to update the game data based on an action taken by the player or an NPC
            void EndTurn(const Map::Map&);
        private:
            std::vector<Observer*> observers;

		    std::string observerMessage;

            Campaign* gameCampaign;
    };
}