#pragma once
/*!
* \file Map.h
* \brief Header file for the Map class
*
* @author Michelle Polonsky
*/
#pragma once 
#include "Interactable.h"
#include "Character.h"
#include "item.h"
#include "EmptyCell.h"
#include <vector>
#include <string>

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
	class Map {
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
		
	private:
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
