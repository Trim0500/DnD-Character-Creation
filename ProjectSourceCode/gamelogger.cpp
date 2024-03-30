#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <time.h>

#include "gamelogger.h"

#define LOG_FILE_DIR "\\Game Log\\Game_Log.txt"

namespace {
    std::string CreateLogMessage(const std::string& _observableMessage) {
        time_t now = time(NULL);
        char dateTimeString[26] = {};
        ctime_s(dateTimeString, 26, &now);

        dateTimeString[24] = '\0';

        std::ostringstream logMessage;
        logMessage <<  "[" << dateTimeString << "] " << _observableMessage;

        return logMessage.str();
    }
}

namespace gamelogger {
    void GameLogger::update(std::string _receivedMessage) {
        messageFromObservable = CreateLogMessage(_receivedMessage);

        std::string currentPath = std::filesystem::current_path().string();

        std::ostringstream fullURI;
        fullURI << currentPath << LOG_FILE_DIR;

        if (!firstMessageOfSession) {
            std::ofstream logFile(fullURI.str());
            logFile << messageFromObservable;

            logFile.close();

            firstMessageOfSession = true;
        }
        else {
            std::ofstream logFile(fullURI.str(), std::ios::app);
            logFile << '\n' << messageFromObservable;

            logFile.close();
        }
    }
}