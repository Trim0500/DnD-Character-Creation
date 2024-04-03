#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <sys/stat.h>
#include <regex>

#include "testgamelogger.h"

#define LOG_FILE_DIR "\\Game Log\\Game_Log.txt"
#define TEST_MESSAGE_1 "[TestGameLogger/TestUpdate] -- This is random ass text"
#define TEST_MESSAGE_2 "[TestGameLogger/TestUpdate] -- This is another random ass text"
#define TEST_MESSAGE_3 "[TestGameLogger/TestUpdate] -- This is the last random ass text"

void TestGameLogger::setUp(void) {
    noArgsLoggerObject = new GameLogger();
    
    gameObject = new Game();

    customLoggerObject = new GameLogger(gameObject);
}

void TestGameLogger::tearDown(void) {
    delete noArgsLoggerObject;
    
    gameObject->Detach(customLoggerObject);
    delete gameObject;

    delete customLoggerObject;
}

void TestGameLogger::TestNoArgsLoggerConstructor(void) {
    CPPUNIT_ASSERT(noArgsLoggerObject->GetMessageFromObservable() == "");
    CPPUNIT_ASSERT(noArgsLoggerObject->GetFirstMessageOfSession() == false);
}

void TestGameLogger::TestLoggerConstructor(void) {
    std::vector<Observer*> gameObservers = gameObject->GetObservers();
    CPPUNIT_ASSERT(customLoggerObject == gameObservers[0]);
    CPPUNIT_ASSERT(customLoggerObject->GetMessageFromObservable() == "");
    CPPUNIT_ASSERT(customLoggerObject->GetFirstMessageOfSession() == false);
}

void TestGameLogger::TestUpdate(void) {
    std::string currentPath = std::filesystem::current_path().string();

	std::ostringstream folderURI;
	folderURI << currentPath << LOG_FILE_DIR;
    
    std::ostringstream existingLogFilePath;
    existingLogFilePath << folderURI.str();

    std::string testMessage = TEST_MESSAGE_1;
    noArgsLoggerObject->update(testMessage);
    
    struct stat existingLogFileBuffer;
	CPPUNIT_ASSERT(stat(existingLogFilePath.str().c_str(), &existingLogFileBuffer) == 0);

    std::string testMessage2 = TEST_MESSAGE_2;
    noArgsLoggerObject->update(testMessage2);
    
    std::string testMessage3 = TEST_MESSAGE_3;
    noArgsLoggerObject->update(testMessage3);

    std::smatch match;

    std::regex logMessage1Rgx("\\[TestGameLogger\\/TestUpdate\\] -- This is random ass text");
    std::regex logMessage2Rgx("\\[TestGameLogger\\/TestUpdate\\] -- This is another random ass text");
    std::regex logMessage3Rgx("\\[TestGameLogger\\/TestUpdate\\] -- This is the last random ass text");

    int lineCount = 1;

    std::ifstream campaignFileInputStream(existingLogFilePath.str());
    while (!campaignFileInputStream.eof()) {
        std::string nextLine = "";
        std::getline(campaignFileInputStream, nextLine);

        if (nextLine.empty()) {
            continue;
        }
        
        switch (lineCount) {
            case 1:
                CPPUNIT_ASSERT(regex_search(nextLine, match, logMessage1Rgx));

                break;
            case 2:
                CPPUNIT_ASSERT(regex_search(nextLine, match, logMessage2Rgx));

                break;
            case 3:
                CPPUNIT_ASSERT(regex_search(nextLine, match, logMessage3Rgx));

                break;
            default:
                break;
        }

        lineCount++;
    }
}
