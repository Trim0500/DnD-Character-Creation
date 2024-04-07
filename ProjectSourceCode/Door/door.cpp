#include <string>
#include <fstream>
#include <sstream>
#include <regex>

#include "door.h"

namespace 
{
    std::string BuildVectorCSVOutput(const std::vector<int>& _IDs) {
        std::ostringstream result;
        result << "[";

        int idsSize = _IDs.size();
        for (int i = 0; i < idsSize; i++)
        {
            if (i + 1 == idsSize) {
                result << std::to_string(_IDs[i]);

                break;
            }

            result << std::to_string(_IDs[i]) << ":";
        }

        result << "]";

        return result.str();
    }

    std::string BuildDoorsOutput(const std::vector<door::Door*>& _doorsToSave) {
        std::string outputResult;

		std::ostringstream csvOutput;
		for (int i = 0; i < (int)_doorsToSave.size(); i++)
		{
			csvOutput << _doorsToSave[i]->GetDoorID() <<
                            "," <<
                            _doorsToSave[i]->GetFirstMapID() <<
                            "," <<
                            _doorsToSave[i]->GetSecondMapID() <<
                            "," <<
                            BuildVectorCSVOutput(_doorsToSave[i]->GetFirstMapLocation()) <<
                            "," <<
                            BuildVectorCSVOutput(_doorsToSave[i]->GetSecondMapLocation()) <<
                            "," <<
                            BuildVectorCSVOutput(_doorsToSave[i]->GetFirstMapSpawnPoint()) <<
                            "," <<
                            BuildVectorCSVOutput(_doorsToSave[i]->GetSecondMapSpawnPoint()) <<
                            std::endl;
		}

		return csvOutput.str();
    }

    std::vector<int> BuildIDVector(std::string _vectorString) {
        std::vector<int> result;
        
        std::smatch match;

        std::regex numberRgx("[0-9]+");

        while (regex_search(_vectorString, match, numberRgx)) {
            result.push_back(std::stoi(match.str()));

            _vectorString = match.suffix().str();
        }

        return result;
    }

    std::vector<door::Door*> GetDoors(std::ifstream* _fileStream) {
        std::vector<door::Door*> resultVector;

		while (!_fileStream->eof()) {
			std::string nextLine = "";
			std::getline(*_fileStream, nextLine);
			if (nextLine.empty()) {
				continue;
			}

			std::stringstream lineStream(nextLine);

			std::vector<std::string> segmentList;

			std::string segment = "";
			while (std::getline(lineStream, segment, ',')) {
				segmentList.push_back(segment);
			}

            door::Door* foundDoor = new door::Door(std::stoi(segmentList[0]),
                                                    std::stoi(segmentList[1]),
                                                    std::stoi(segmentList[2]),
                                                    BuildIDVector(segmentList[3]),
                                                    BuildIDVector(segmentList[4]),
                                                    BuildIDVector(segmentList[5]),
                                                    BuildIDVector(segmentList[6]));
            resultVector.push_back(foundDoor);
		}

		return resultVector;
    }
}

namespace door {
    DoorDestinationInfo Door::UseDoor(const int& _mapID) {
        DoorDestinationInfo result;

        result.mapID = _mapID == firstMapID ? secondMapID : firstMapID;
        result.mapLocationX = _mapID == firstMapID ? secondMapLocation[0] : firstMapLocation[0];
        result.mapLocationY = _mapID == firstMapID ? secondMapLocation[1] : firstMapLocation[1];
        result.destinationX = _mapID == firstMapID ? secondMapSpawnPoint[0] : firstMapSpawnPoint[0];
        result.destinationY = _mapID == firstMapID ? secondMapSpawnPoint[1] : firstMapSpawnPoint[1];

        return result;
    }

    void SaveDoors(const std::string& _fileURI, const std::vector<Door*>& _doorsToSave) {
		std::string csvOutput = BuildDoorsOutput(_doorsToSave);

		std::ofstream doorOutputStream(_fileURI);
		doorOutputStream << csvOutput;

		doorOutputStream.close();
    }

    std::vector<Door*> LoadDoors(const std::string& _fileURI) {
        std::ifstream doorInputStream(_fileURI);
		if (!doorInputStream.is_open()) {
			throw std::invalid_argument("Failed to open the file at: " + _fileURI);
		}

		std::vector<Door*> doorRecords = GetDoors(&doorInputStream);

		doorInputStream.close();

		return doorRecords;
    }
}

