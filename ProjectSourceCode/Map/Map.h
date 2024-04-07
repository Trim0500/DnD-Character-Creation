#pragma once
/*!
* \file Map.h
* \brief Header file for the Map class
*
* @author Michelle Polonsky
*/

#pragma once 

#include <vector>
#include <string>
#include <typeinfo>

#include "..\Interactable\Interactable.h"
#include "..\Character/Character.h"
#include "..\Item\item.h"
#include "..\Observer\Observable.h"
#include "..\Interactable\EmptyCell.h"

using namespace observable;


/*!
* \namespace Map
* \brief namespace to encapsulate Map navigation
*/
namespace Map {

	/*!
	* \var dirs
	* \brief all possible directions to look in : down, right, up, back
	*/
	const std::vector<std::pair<int, int>> dirs = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

	/*!
	* \class Map
	* \brief Class to encapsulate the map functionality
	*/
	class Map : public Observable {
	public:
		/*!
		* \fn Map
		* \brief Constructor to build a basic map provided by user
		*/
		Map();

		/*!
		* \fn Map
		* \brief Constructor to build a basic map provided by user
		*/
		Map(int rows, int cols);

		void Attach (Observer* _observer) override { observers.push_back(_observer); };

		void Detach (Observer* _observer) override { observers.erase(std::remove(observers.begin(), observers.end(), _observer), observers.end()); };

		/*!
		* \fn Notify
		* \brief Implemented function that will use the list of this observers and call their update functions using the instances observer message
		*/
		void Notify() override;

		/*!
		* \fn CreateObserverMessage
		* \brief Function that will take in a message from a calling object and use it to notify the observers with that message
		* 
		* \param _message String representing the message to pass to the observers of this game instance. Default of "Empty"
		*/
		void CreateObserverMessage(std::string);

		std::vector<Observer*> GetObservers() { return observers; };

		void SetObservers(const std::vector<Observer*>& _observers) { observers = _observers; };

		std::string GetObserverMessage() { return observerMessage; };

		void SetObserverMessage(const std::string& _observerMessage) { observerMessage = _observerMessage; };

		/*!
		* \brief Getters
		*/
		int GetMapID() { return mapID; };
		const int getRows() { return rows; };
		const int getCols() { return cols; };
		const int* getEnd_Cell() { return endCell; };
		const std::vector<std::vector<Interactable::Interactable*>> getGrid() { return grid; };

		/*!
		* \brief Setters 
		*/
		void setRows(int rows);
		void setCols(int cols);
		void setGrid();
		void setEndCell(int row, int col);
		void setStartCell(int row, int col);

		void setCell(int row, int col, Interactable::Interactable* cell);

		void setEmpty(int row, int col);
		void setWall(int row, int col);
		void setCharacter(int row, int col, Character::Character* cha);
		void setItem(int row, int col, item::Item* cha);

		/*!
		* \fn IsTherePath
		* \brief Check if there is a possible passage through the map
		*/
		bool IsTherePath();

		/*!
		* \fn ValidCell
		* \brief Check if the given x,y coordinates are a valid cell to step on
		*/
		bool ValidCell(int row, int col, std::vector<std::vector<bool>> visitde);

		void MoveCharacter(const int&, const int&, Character::Character*);

		void printMap();

		void GetCharacterCoordinates(int& x, int& y, Character::Character* t_character);

		std::vector<Character::Character*> GetCharactersInMap();

		void Print();

	private:
		/*!
		* \var observers
		* \brief Vector of pointers to Observer instances representing the attached objects that are to be notified of state changes
		*/
		std::vector<Observer*> observers;

		/*!
		* \var observerMessage
		* \brief String representing the message to pass to the observers
		*/
		std::string observerMessage;

		/*!
		*
		*/
		static inline int nextMapID = 0;
		/*!
		* \var mapID
		* \brief Integer representing the unique ID for the instance of the map
		*/
		int mapID;
		/*!
		* \var rows
		* \brief rows/height/x
		*/
		int rows;
		/*!
		* \var cols
		* \brief columns/width/y
		*/
		int cols;
		/*!
		* \var end_cell
		* \brief start = upper right cell, ie: 0,0, end = lower left cell, ie: cols.length-1, rows.lenght-1
		*/
		int endCell[2];

		int startCell[2];

		/*!
		* \var grid
		* \brief grid mapping out the cell types
		*/
		std::vector<std::vector<Interactable::Interactable*>> grid;
	};

}
