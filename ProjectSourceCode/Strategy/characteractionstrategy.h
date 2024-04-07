/*!
* \file characteractionstrategy.h
* \brief File that contains the interface for the movement strategy pattern for characters
* \author Tristan Lafleur
*/

#pragma once

#include <vector>
#include <string>

#include "..\Interactable\Interactable.h"

/*!
* \namespace characteractionstrategy
* \brief namespace to encapsulate strategy pattern functionality
*/
namespace characteractionstrategy {
    /*!
    * \struct CellActionInfo
    * \brief struct to represent the necessary info to inform the game about the actions a character may take
    */
    struct CellActionInfo {
        /*!
        * \var row 
        * \brief Index of the cell's row
        */
        int row = 0;
        /*!
        * \var col 
        * \brief Index of the cell's column
        */
        int col = 0;
        /*!
        * \var cellColor 
        * \brief String that represents the intended highlighting of the cell
        */
        std::string cellColor = "";
        /*!
        * \var actionName 
        * \brief String that represents the intended action of the cell
        */
        std::string actionName = "";
    };

    /*!
    * \class CharacterActionStrategy
    * \brief interface to be implemented by other classes that has the declaration of the strategy algo
    */
    class CharacterActionStrategy {
        public:
            /*!
            * \fn ~CharacterActionStrategy
            * \brief default virtual destructor
            */
            virtual ~CharacterActionStrategy() = default;

            /*!
            * \fn UseMovementStrategy
            * \brief Abstract function that is meant to be implemented by other classes
            * 
            * \param _currentMap A 2D grid that represents the map the character finds themselves in
            * \param _row Integer that represents the current row index of the character location (1-indexed)
            * \param _col Integer that represents the current column index of the character location (1-indexed)
            * 
            * \return Vector of CellActionInfo structs that represents the possible actions that can be done in the cardinal directions
            */
            virtual std::vector<CellActionInfo> UseMovementStrategy(std::vector<std::vector<Interactable::Interactable*>>, const int&, const int&) const = 0;
    };
}
