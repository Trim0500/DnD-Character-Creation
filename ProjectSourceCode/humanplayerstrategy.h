/*!
* \file humanplayerstrategy.h
* \brief File that contains the forward declarations for the movement strategy pattern for player characters
* \author Tristan Lafleur
*/

#pragma once

#include "characteractionstrategy.h"

using namespace characteractionstrategy;

/*!
* \namespace humanplayerstrategy
* \brief namespace to encapsulate player movement impl of the strategy pattern
*/
namespace humanplayerstrategy {
    /*!
    * \class HumanPlayerStrategy
    * \brief Class that implements the CharacterActionStrategy interface
    */
    class HumanPlayerStrategy : public CharacterActionStrategy {
        public:
            /*!
            * \fn UseMovementStrategy
            * \brief Overriden function that establishes the posible actions a player may take in the cardinal directions of their current position
            * 
            * \param _currentMap A 2D grid that represents the map the character finds themselves in
            * \param _row Integer that represents the current row index of the character location
            * \param _col Integer that represents the current column index of the character location
            * 
            * \return Vector of CellActionInfo structs that represents the possible actions that can be done in the cardinal directions
            */
            std::vector<CellActionInfo> UseMovementStrategy(std::vector<std::vector<Interactable::Interactable*>>, const int&, const int&) const override;
    };
}
