#pragma once

#include <string>

#include "Observer.h"

using namespace observer;

namespace gamelogger
{
    class GameLogger : public Observer {
        public:
            GameLogger(){};

            virtual ~GameLogger(){};

            void update(std::string) override;
        private:
            std::string messageFromObservable;
    };
}
