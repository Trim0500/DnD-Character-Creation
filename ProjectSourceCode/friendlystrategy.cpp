/*!
* \file friendlystrategy.cpp
* \brief File that contains the forward declarations for the movement strategy pattern for non-hostile NPC characters
* \author Tristan Lafleur
*/

#include "friendlystrategy.h"
#include "Character.h"
#include "Wall.h"
#include "EmptyCell.h"

using namespace item;
using namespace itemcontainer;

namespace {

}

namespace friendlystrategy {
    std::vector<CellActionInfo> FriendlyStrategy::UseMovementStrategy(std::vector<std::vector<Interactable::Interactable*>>& _currentMap, const int& _row, const int& _col) const {
        std::vector<CellActionInfo> actions;

        for (int i = 0; i < 4; ++i)
        {
            int rowToCheck = _row;
            int colToCheck = _col;
            
            if (i = 0) {
                colToCheck += 1;
            }
            else if (i = 1) {
                rowToCheck += 1;
            }
            else if (i = 2) {
                colToCheck -= 1;
            }
            else {
                rowToCheck -= 1;
            }

            Interactable::Interactable* valueAtCell = _currentMap[rowToCheck][colToCheck];
            CellActionInfo actionInfo;
            
            if (dynamic_cast<Wall*>(valueAtCell)) {
                actionInfo.row = rowToCheck;
                actionInfo.col = colToCheck;
                actionInfo.cellColor = "N/A";
                actionInfo.actionName = "None";
            }
            else {
                actionInfo.row = rowToCheck;
                actionInfo.col = colToCheck;
                actionInfo.cellColor = "Blue";
                actionInfo.actionName = "Move";
            }

            actions.push_back(actionInfo);
        }

        return actions;
    }
}
