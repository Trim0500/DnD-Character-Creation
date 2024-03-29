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
            GameLogger() { messageFromObservable = ""; firstMessageOfSession = false; };

            GameLogger(Observable* _observable) { _observable->Attach(this); messageFromObservable = ""; firstMessageOfSession = false; };

            virtual ~GameLogger(){};

            void update(std::string) override;

            std::string GetMessageFromObservable() { return messageFromObservable; };

            void SetMessageFromObservable (const std::string& _messageFromObservable) { messageFromObservable = _messageFromObservable; };

            bool GetFirstMessageOfSession() { return firstMessageOfSession; };

            void SetFirstMessageOfSession(bool _firstMessageOfSession) { firstMessageOfSession = _firstMessageOfSession; };
        private:
            std::string messageFromObservable;

            bool firstMessageOfSession;
    };
}
