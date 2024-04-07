#include "door.h"

namespace 
{
    
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
}

