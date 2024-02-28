/*!
* \file Map.h
* \brief Header file for the Map class
*
* @author Michelle Polonsky
*/

#include <vector>
#include <string>

using namespace std;

/*!
* \namespace Map
* \brief namespace to encapsulate Map navigation
*/
namespace Map {

	/*!
	* \enum Cell_Type
	* \brief Enum to represent the posible cell types on a map
	*/
	enum class Cell_Type {
		empty='_',//empty cell, character can move through it.
		wall='w',//wall cell, character cannot move through it.
		special='s'//special cell, character has a special interraction, can move after interraction.
	};

	/*!
	* \fn ConvertToCellType
	* \brief Free function to take a letter and attempt to map it to a cell type
	*/
	Cell_Type ConvertToCellType(char letter);

	/*!
	* \var dirs
	* \brief all possible directions to look in : down, right, up, back
	*/
	const vector<pair<int, int>> dirs = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

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
		Map(int rows, int cols);

		const int Rows() { return rows; };
		const int Cols() { return cols; };
		const int* End_Cell() { return end_cell; };
		const vector<vector<Cell_Type>>& Grid() { return grid; };

		/*!
		* \fn Create
		* \brief Prompts user for map inputs
		*/ 
		static Map* Create();

		/*!
		* \fn Customize
		* \brief Let's user customize the map until they want to stop
		*/
		void Customize();

		/*!
		* \fn KeepCustomizing
		* \brief Checks if the user wants to keep customizing the map
		*/
		bool KeepCustomizing();

		/*!
		* \fn Print
		* \brief Print the grid with each cell type
		*/
		void Print();

		/*!
		* \fn IsTherePath
		* \brief Check if there is a possible passage through the map
		*/
		bool IsTherePath();

		/*!
		* \fn ValidCell
		* \brief Check if the given x,y coordinates are a valid cell to step on
		*/
		bool ValidCell(int row, int col, vector<vector<bool>> visitde);

		//DEBUG ONLY
		void ChangeCell(int row, int col, Cell_Type);
	
	private:
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
		int end_cell[2];

		/*!
		* \var grid
		* \brief grid mapping out the cell types
		*/
		vector<vector<Cell_Type>> grid;
	};

}
