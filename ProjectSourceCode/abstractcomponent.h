/*!
* \file abstractcomponent.h
* \brief File that provides the interface for the Componenet of the Decorator pattern
* \author Tristan Lafleur (40245238)
*/

#pragma once

#include <vector>

/*!
* \namespace abstractcomponent
* \brief Namespace that encasulates the functionality for the AbstractComponenet class
*/
namespace abstractcomponent
{
    /*!
    * \class AbstractComponent
    * \brief Class that provides the virtual methods to override for the concrete implementations of the decorator components
    */
    class AbstractComponent
    {
        public:
            /*!
            * \fn Ability_Score_Natural
            * \brief Virtual function that is meant to be overriden to get the particular ability score of a character
            */
            virtual int Ability_Score_Natural(int, int) { return 0; };

            virtual int ModifierDecorator(int) { return 0; }

            /*!
            * \fn GetDecoratorList
            * \brief Virtual function that is meant to be overriden to establish the decorators in play
            */
            virtual std::vector<AbstractComponent*> GetDecoratorList() { std::vector<AbstractComponent*> initDecorators; return initDecorators; };
    };
}

