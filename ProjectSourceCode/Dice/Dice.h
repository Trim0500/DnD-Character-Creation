/*! 
* \brief Header file containing Dice functionality definitions
* This is a dice rolling system for D&D 5e
* Queries are formatted as `xdy[+/-z]`, which rolls a die of y sides x times, then adds or subtracts z.
* There are two ways to use it, either:
* \begin{verbatim}
* int rolled_value = Dice::roll(query);
* \end{verbatim}
* or 
* \begin{verbatim}
* Dice die = Dice(query);
* int rolled_vale = die.roll();
* \end{verbatim}
*/

#ifndef DICE_H
#define DICE_H

// #include <time.h>
#include <ctime>
#include <iostream>
#include <regex>
#include <string>

#include "..\Observer\Observable.h"

using namespace observable;

static std::regex DICE("^([0-9]+)d(4|6|8|10|12|20|100)((?:\\+|-)[0-9]*)*$");

class Dice : public Observable {
	public:
		/*!
		* @brief Dice object constructor
		* @param query string query under format xdy[+/-z]
		*/
		Dice(std::string query);
		/*!
		* @brief Default constructor.
		*/
		Dice();

		virtual ~Dice(){};

		void Attach (Observer* _observer) override { observers.push_back(_observer); };

		void Detach (Observer* _observer) override { observers.erase(std::remove(observers.begin(), observers.end(), _observer), observers.end()); };

		void Notify() override;

		void CreateObserverMessage(std::string);

		/*!
		* @brief Rolls a given query
		* @param query the query to be rolled
		* @return result of the dice roll
		*/
		static int roll(std::string query);
		
		/*!
		* @brief Rolls given query twice, keeping highest
		* @param query the query to be rolled
		* @return result of dice roll
		*/
		static int roll_with_advantage(std::string query);

		/*!
		* @brief Rolls given query twice, keeping lowest
		* @param query the query to be rolled
		* @return result of dice roll
		*/
		static int roll_with_disadvantage(std::string query);

		/*!
		* @brief Roll the dice object
		* @return value of the roll
		*/
		int roll();

		/*!
		* @brief Roll the dice object twice, keeping highest
		* @return value of the roll
		*/
		int roll_with_advantage();

		/*!
		* @brief Roll the dice object twice, keeping lowest
		* @return value of the roll
		*/
		int roll_with_disadvantage();

		/*!
		* @brief increases the number of die (x in query) by 1
		*/
		void add_die();

		/*!
		* @brief increases the number of dice (x in query) by amount
		* @param amount amount the increase number of dice by
		*/
		void add_die(int amount);

		/*!
		* @brief generates a std::string representation of the dice
		* @return std::string repr of die
		*/
		std::string get_string();

		/*!
		* @brief leading_multipler getter
		* @return leading multipler
		*/
		int get_leading_multiplier();

		/*!
		* @brief die_sides getter
		* @return dice's number of sides
		*/
		int get_die_sides();

		/*!
		* @brief addition getter
		* @return number to add after roll
		*/
		int get_addition();
	private:
		static inline std::vector<Observer*> observers;

		static inline std::string observerMessage;

		/*!
		* @brief x, number of dice to roll
		*/
		int leading_multiplier=1;
		/*!
		* @brief number of dice sides
		*/
		int die_sides=4;
		/*!
		* @brief value to add after rolling
		*/
		int addition=0;
};

#endif
