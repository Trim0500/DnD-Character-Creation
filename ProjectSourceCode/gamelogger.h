#pragma once

#include <string>

#include "Observer.h"
#include "Observable.h"

using namespace observer;
using namespace observable;

namespace gamelogger
{
    class GameLogger : public Observer {
        public:
            GameLogger(Observable* _observable) { _observable->Attach(this); firstMessageOfSession = false; };

            virtual ~GameLogger(){};

            void update(std::string) override;
        private:
            std::string messageFromObservable;

            bool firstMessageOfSession;
    };
}
