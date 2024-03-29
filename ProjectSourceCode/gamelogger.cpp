#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <chrono>
#include <ctime>

#include "gamelogger.h"

#define LOG_FILE_DIR "\\Game Log\\Game_Log.txt"

namespace {
    std::string CreateLogMessage(const std::string& _observableMessage) {
        auto currentTime = std::chrono::system_clock::now();
        std::time_t formmattedTime = std::chrono::system_clock::to_time_t(currentTime);

        std::ostringstream logMessage;
        logMessage <<  "[" << std::ctime(&formmattedTime) << "] " << _observableMessage;

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
            logFile << messageFromObservable;

            logFile.close();
        }
    }
}