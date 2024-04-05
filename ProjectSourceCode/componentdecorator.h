/*!
* \file componentdecorator.h
* \brief File that provides the interface for the Decorator of the Decorator pattern
* \author Tristan Lafleur (40245238)
*/

#pragma once

#include "abstractcomponent.h";

using namespace abstractcomponent;

/*!
* \namespace componentdecorator
* \brief Namespace that encasulates the functionality for the ComponentDecorator class
*/
namespace componentdecorator {
    /*!
    * \class ComponentDecorator
    * \brief Class that implements the AbstractComponent interface
    */
    class ComponentDecorator : public AbstractComponent
    {
        public: 
            /*!
            * \fn ComponentDecorator
            * \brief No-args constructor for the ComponentDecorator class meant to be used for when Items are not equipped to a character
            */
            ComponentDecorator() { wrappee = nullptr; };

            /*!
            * \fn ComponentDecorator
            * \brief Custom constructor for the ComponentDecorator class meant to be used for when Characters are loaded into a game
            */
            ComponentDecorator(AbstractComponent* _wrappee) { wrappee = _wrappee; };
            
            /*!
            * \fn Ability_Score_Natural
            * \brief Overriden function that is meant to use the wrappee's function of the same name as a baseline for derived classes
            */
            int Ability_Score_Natural(int, int) override;

            virtual int ModifierDecorator(int) override;

            /*!
            * \fn GetDecoratorList
            * \brief Overriden function that is meant to use the wrappee's function of the same name as a baseline for concete implementations
            */
            std::vector<AbstractComponent*> GetDecoratorList() override;
        protected:
            /*!
            * \var wrappee Pointer to an instance of the AbstractComponenet class. Mostly ends up being Items while the baseline is a Character
            */
            AbstractComponent* wrappee;
    };
}
