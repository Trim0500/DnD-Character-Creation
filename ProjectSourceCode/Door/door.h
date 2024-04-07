#pragma once

#include <vector>

#include "..\Interactable\Interactable.h"

namespace door {
    struct DoorDestinationInfo
    {
        int destinationX;

        int destinationY;

        int mapID;
    };
    

    class Door : public Interactable::Interactable {
        public:
            Door() { nextDoorID++; doorID = nextDoorID; };

            Door(int _doorID, int _firstMapID, int _secondMapID, std::vector<int> _firstMapSpawnPoint, std::vector<int> _secondMapSpawnPoint)
            {
                doorID = _doorID;
                firstMapID = _firstMapID;
                secondMapID = _secondMapID;
                firstMapSpawnPoint = _firstMapSpawnPoint;
                secondMapSpawnPoint = _secondMapSpawnPoint;
            };

            Door(Door& _door) {
                doorID = _door.doorID;
                firstMapID = _door.firstMapID;
                secondMapID = _door.secondMapID;
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

            std::vector<int> firstMapSpawnPoint;

            std::vector<int> secondMapSpawnPoint;
    };
}
