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
		void setRows(int _rows) { rows = _rows; };
		void setCols(int _cols) { cols = _cols; };
		void setGrid();
		void setEndCell();

		void setCell(int row, int col, Interactable::Interactable* cell);

		void setEmpty(int row, int col);
		void setWall(int row, int col);
		void setCharacter(int row, int col, Character::Character* cha);
		void setItem(int row, int col, item::Item* cha);

		/*!
		* \fn Create
		* \brief Prompts user for map inputs
		*/
		//static Map* Create();

		/*!
		* \fn Customize
		* \brief Let's user customize the map until they want to stop
		*/
		//void Customize();

		/*!
		* \fn KeepCustomizing
		* \brief Checks if the user wants to keep customizing the map
		*/
		//bool KeepCustomizing();

		/*!
		* \fn Print
		* \brief Print the grid with each cell type
		*/
		//void Print();

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
		
		bool ValidCellInteractable(int nextRow, int nextCol, std::vector<std::vector<bool>> visited);

	private:
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

		/*!
		* \var grid
		* \brief grid mapping out the cell types
		*/
		std::vector<std::vector<Interactable::Interactable*>> grid;
	};

}
