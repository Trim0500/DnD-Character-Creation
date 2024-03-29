#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <sys/stat.h>

#include "testgamelogger.h"

#define MAP_ROW_COUNT 5
#define MAP_COL_COUNT 5
#define LOG_FILE_DIR "\\Test Game Log\\Test_Game_Log.txt"
#define LOG_FILE_2_DIR "\\Test Game Log\\Test_Game_Log_2.txt"

void TestGameLogger::setUp(void) {
    noArgsLoggerObject = new GameLogger();
    
    gameObject = new Game();

    mapObject = new Map::Map(MAP_ROW_COUNT, MAP_COL_COUNT);

    characterObject = new Character::Character("Testaniel Unitoph",Character::Character_Class::Fighter, false, new AggressorStrategy());

    customLoggerObject = new GameLogger(gameObject);
    mapObject->Attach(customLoggerObject);
    characterObject->Attach(customLoggerObject);
}

void TestGameLogger::tearDown(void) {
    gameObject->Detach(customLoggerObject);
    delete gameObject;

    mapObject->Detach(customLoggerObject);
    delete mapObject;

    characterObject->Detach(customLoggerObject);
    delete characterObject;

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

    noArgsLoggerObject->update("[TestGameLogger/TestUpdate] -- This is random ass text");
    
    struct stat existingLogFileBuffer;
	CPPUNIT_ASSERT(stat(existingLogFilePath.str().c_str(), &existingLogFileBuffer) == 0);
}
