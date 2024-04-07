/*!
* \file friendlystrategy.cpp
* \brief File that contains the forward declarations for the movement strategy pattern for non-hostile NPC characters
* \author Tristan Lafleur
*/

#include "friendlystrategy.h"
#include "..\Character.h"
#include "..\Wall.h"
#include "..\EmptyCell.h"

using namespace item;
using namespace itemcontainer;

namespace {

}

namespace friendlystrategy {
    std::vector<CellActionInfo> FriendlyStrategy::UseMovementStrategy(std::vector<std::vector<Interactable::Interactable*>> _currentMap, const int& _row, const int& _col) const {
        std::vector<CellActionInfo> actions;

        for (int i = 0; i < 4; i++)
        {
            int rowToCheck = _row;
            int colToCheck = _col;
            
            if (i == 0) {
                rowToCheck -= 1;
            }
            else if (i == 1) {
                colToCheck += 1;
            }
            else if (i == 2) {
                rowToCheck += 1;
            }
            else {
                colToCheck -= 1;
            }

            if (rowToCheck < 1 || rowToCheck > _currentMap.size() || colToCheck < 1 || colToCheck > _currentMap[0].size()) {
                continue;
            }

            Interactable::Interactable* valueAtCell = _currentMap[rowToCheck - 1][colToCheck - 1];
            CellActionInfo actionInfo;
            
            if (dynamic_cast<Wall*>(valueAtCell) || dynamic_cast<Character::Character*>(valueAtCell) || dynamic_cast<ItemContainer*>(valueAtCell)) {
                actionInfo.row = rowToCheck;
                actionInfo.col = colToCheck;
                actionInfo.cellColor = Character::WALL_CELL_COLOR;
                actionInfo.actionName = Character::WALL_CELL_ACTION;
            }
            else {
                actionInfo.row = rowToCheck;
                actionInfo.col = colToCheck;
                actionInfo.cellColor = Character::EMPTY_CELL_COLOR;
                actionInfo.actionName = Character::EMPTY_CELL_ACTION;
            }

            actions.push_back(actionInfo);
        }

        return actions;
    }
}
