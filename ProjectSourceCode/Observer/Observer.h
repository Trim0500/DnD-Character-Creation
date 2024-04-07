/*!
* \file Observer.h
* \brief File that establishes the interface for observer concrete implementations
*
* @author Tristan Lafleur (40245238)
*/

#include <string>

#pragma once

/*!
* \namespace observer
* \brief Namespace to partition the Observer functionality
*/
namespace observer {
	/*!
    * \class Observer
    * \brief Class to abstract the observer functionality
    */
	class Observer {
		public:
			/*!
            * \fn ~Observer
            * \brief Destructor for Observer
            */
			virtual ~Observer() {};

			/*!
            * \fn update
            * \brief Abstract function to provide concrete implementations a way to override using static string
            */
			virtual void update(std::string) = 0;
			
			/*!
            * \fn update
            * \brief Abstract function to provide concrete implementations a way to override using void pointers
            */
			virtual void update(void*) const = 0;
	};
}