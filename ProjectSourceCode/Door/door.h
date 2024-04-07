#pragma once

#include <vector>

#include "..\Interactable\Interactable.h"

namespace door {
    struct DoorDestinationInfo
    {
        int mapID;

        int mapLocationX; // 1-indexed

        int mapLocationY; // 1-indexed

        int destinationX; // 1-indexed

        int destinationY; // 1-indexed
    };
    

    class Door : public Interactable::Interactable {
        public:
            Door() { nextDoorID++; doorID = nextDoorID; };

            Door(int _doorID,
                    int _firstMapID,
                    int _secondMapID,
                    std::vector<int> _firstMapLocation,
                    std::vector<int> _secondMapLocation,
                    std::vector<int> _firstMapSpawnPoint,
                    std::vector<int> _secondMapSpawnPoint)
            {
                doorID = _doorID;
                firstMapID = _firstMapID;
                secondMapID = _secondMapID;
                firstMapLocation = _firstMapLocation;
                secondMapLocation = _secondMapLocation;
                firstMapSpawnPoint = _firstMapSpawnPoint;
                secondMapSpawnPoint = _secondMapSpawnPoint;
            };

            Door(Door& _door) {
                doorID = _door.doorID;
                firstMapID = _door.firstMapID;
                secondMapID = _door.secondMapID;
                firstMapLocation = _door.firstMapLocation;
                secondMapLocation = _door.secondMapLocation;
                firstMapSpawnPoint = _door.firstMapSpawnPoint;
                secondMapSpawnPoint = _door.secondMapSpawnPoint;
            }

            ~Door() { firstMapSpawnPoint.clear(); secondMapSpawnPoint.clear(); };

            int GetNextDoorID() { return nextDoorID; };

            void SetNextDoorID(int _nextDoorID) { nextDoorID = _nextDoorID; };
            
            int GetDoorID() { return doorID; };

            void SetDoorID(int _doorID) { doorID = _doorID; };
            
            int GetFirstMapID() { return firstMapID; };

            void SetFirstMapID(int _firstMapID) { firstMapID = _firstMapID; };
            
            int GetSecondMapID() { return secondMapID; };

            void SetSecondMapID(int _secondMapID) { secondMapID = _secondMapID; };
            
            std::vector<int> GetFirstMapLocation() { return firstMapLocation; };

            void SetFirstMapLocation(std::vector<int> _firstMapLocation) { firstMapLocation = _firstMapLocation; };
            
            std::vector<int> GetSecondMapLocation() { return secondMapLocation; };

            void SetSecondMapLocation(std::vector<int> _secondMapLocation) { secondMapLocation = _secondMapLocation; };

            std::vector<int> GetFirstMapSpawnPoint() { return firstMapSpawnPoint; };

            void SetFirstMapSpawnPoint(std::vector<int> _firstMapSpawnPoint) { firstMapSpawnPoint = _firstMapSpawnPoint; };
            
            std::vector<int> GetSecondMapSpawnPoint() { return secondMapSpawnPoint; };

            void SetSecondMapSpawnPoint(std::vector<int> _secondMapSpawnPoint) { secondMapSpawnPoint = _secondMapSpawnPoint; };

            DoorDestinationInfo UseDoor(const int&);
        private:
            static inline int nextDoorID = 0;

            int doorID;

            int firstMapID;

            int secondMapID;

            std::vector<int> firstMapLocation; //Locations are 1-indexed

            std::vector<int> secondMapLocation; //Locations are 1-indexed

            std::vector<int> firstMapSpawnPoint; //Locations are 1-indexed

            std::vector<int> secondMapSpawnPoint; //Locations are 1-indexed
    };
}
