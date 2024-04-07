#include "door.h"

namespace 
{
    
}

namespace door {
    DoorDestinationInfo Door::UseDoor(const int& _mapID) {
        DoorDestinationInfo result;

        result.mapID = _mapID == firstMapID ? secondMapID : firstMapID;
        result.destinationX = _mapID == firstMapID ? secondMapSpawnPoint[0] : firstMapSpawnPoint[0];
        result.destinationY = _mapID == firstMapID ? secondMapSpawnPoint[1] : firstMapSpawnPoint[1];

        return result;
    }
}

