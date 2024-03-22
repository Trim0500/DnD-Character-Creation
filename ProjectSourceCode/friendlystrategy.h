/*!
* \file friendlystrategy.h
* \brief File that contains the forward declarations for the movement strategy pattern for non-hostile NPC characters
* \author Tristan Lafleur
*/

#pragma once

#include "characteractionstrategy.h"

using namespace characteractionstrategy;

/*!
* \namespace friendlystrategy
* \brief namespace to encapsulate non-hostile NPC movement impl of the strategy pattern
*/
namespace friendlystrategy {
    /*!
    * \class FriendlyStrategy
    * \brief Class that implements the CharacterActionStrategy interface
    */
    class FriendlyStrategy : public CharacterActionStrategy {
        public:
            /*!
            * \fn UseMovementStrategy
            * \brief Overriden function that establishes the posible actions a non-hostile NPC may take in the cardinal directions of their current position
            * 
            * \param _currentMap A 2D grid that represents the map the character finds themselves in
            * \param _row Integer that represents the current row index of the character location
            * \param _col Integer that represents the current column index of the character location
            * 
            * \return Vector of CellActionInfo structs that represents the possible actions that can be done in the cardinal directions
            */
            std::vector<CellActionInfo> UseMovementStrategy(std::vector<std::vector<Interactable::Interactable*>>&, const int&, const int&) const override;
    };
}
