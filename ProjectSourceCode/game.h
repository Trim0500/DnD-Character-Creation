#pragma once

#include <vector>
#include <string>

#include "Observable.h"

using namespace observable;

namespace game {
    class Game : public Observable {
        public:
            Game(){};

            virtual ~Game(){};

            void Attach (Observer* _observer) override { observers.push_back(_observer); };

            void Detach (Observer* _observer) override { observers.erase(std::remove(observers.begin(), observers.end(), _observer), observers.end()); };

            void Notify() override;

            void CreateObserverMessage(std::string);
        private:
            std::vector<Observer*> observers;

		    std::string observerMessage;
    };
}