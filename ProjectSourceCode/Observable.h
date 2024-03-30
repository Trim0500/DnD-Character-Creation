/*!
* \file Observable.h
* \brief File that establishes the interface for observable concrete implementations
*
* @author Tristan Lafleur (40245238)
*/

#pragma once

#include <list>

#include "Observer.h"

using namespace observer;

/*!
* \namespace observable
* \brief Namespace to partition the Observable functionality
*/
namespace observable {
	/*!
    * \class Observable
    * \brief Class to abstract the observable functionality
    */
	class Observable {
		public: 
			/*!
            * \fn ~Observable
            * \brief Destructor for Observable
            */
			virtual ~Observable() {};

			/*!
            * \fn Attach
            * \brief Abstract function to provide concrete implementations a way to override
            */
			virtual void Attach (Observer*) = 0;

			/*!
            * \fn Detach
            * \brief Abstract function to provide concrete implementations a way to override
            */
			virtual void Detach (Observer*) = 0;

			/*!
            * \fn Notify
            * \brief Abstract function to provide concrete implementations a way to override
            */
			virtual void Notify() = 0;
	};
}