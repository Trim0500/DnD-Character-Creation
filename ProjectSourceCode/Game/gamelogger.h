/*!
* \file gamelogger.h
* \brief File that puts in the forward declarations for the game logger concept
*
* @author Tristan Lafleur (40245238)
*/

#pragma once

#include <string>

#include "..\Observer\Observer.h"
#include "..\Observer\Observable.h"

using namespace observer;
using namespace observable;

/*!
* \namespace gamelogger
* \brief Namespace to partition the Game Logger functionality
*/
namespace gamelogger
{
    /*!
    * \class GameLogger
    * \brief Class to abstract the game logger functionality, implements the Observer interface as a concrete observer
    */    
    class GameLogger : public Observer {
        public:
            /*!
            * \fn GameLogger
            * \brief No args constructor for GameLogger
            */
            GameLogger() { messageFromObservable = ""; firstMessageOfSession = false; };

            /*!
            * \fn GameLogger
            * \brief Custom constructor for GameLogger
            * 
            * \param _observable Pointer to an observable instance to attach this object to
            */
            GameLogger(Observable* _observable) { _observable->Attach(this); messageFromObservable = ""; firstMessageOfSession = false; };

            /*!
            * \fn ~GameLogger
            * \brief Destructor for GameLogger
            */
            virtual ~GameLogger(){};

            /*!
            * \fn update
            * \brief Implemented function to log a message passed to this logger instance
            * 
            * \param _receivedMessage String representing the core message to log into a file passed to this logger instance
            */
            void update(std::string) override;

            void update(void*) const override {};

            std::string GetMessageFromObservable() { return messageFromObservable; };

            void SetMessageFromObservable (const std::string& _messageFromObservable) { messageFromObservable = _messageFromObservable; };

            bool GetFirstMessageOfSession() { return firstMessageOfSession; };

            void SetFirstMessageOfSession(bool _firstMessageOfSession) { firstMessageOfSession = _firstMessageOfSession; };
        private:
            /*!
            * \var messageFromObservable
            * \brief String representing the received message passed from an observable object
            */
            std::string messageFromObservable;

            /*!
            * \var firstMessageOfSession
            * \brief Was the first message received and logged?
            */
            bool firstMessageOfSession;
    };
}
