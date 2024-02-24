#include <vector>
#include <string>


using namespace std;

namespace Map {

	enum class Cell_Type {
		empty='_',//empty cell, character can move through it.
		wall='w',//wall cell, character cannot move through it.
		special='s'//special cell, character has a special interraction, can move after interraction.
	};

	Cell_Type ConvertToCellType(char letter);

	//all possible directions to look in:  down , right ,   up   ,  back
	const vector<pair<int, int>> dirs = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

	class Map {
	public: 
		Map(int rows, int cols);

		const int Rows() { return rows; };
		const int Cols() { return cols; };
		const int End_Cell() { return *end_cell; };

		//Prompts user for map inputs
		static Map* Create();

		//Let's user customize the map until they want to stop
		void Customize();

		//Checks if the user wants to keep customizing the map
		bool KeepCustomizing();

		//Print the grid with each cell type
		void Print();

		//Check if there is a possible passage through the map
		bool IsTherePath();

		//Check if the given x,y coordinates are a valid cell to step on
		bool ValidCell(int row, int col, vector<vector<bool>> visitde);
	
	private:
		int rows; // rows/height/x
		int cols; // columns/width/y

		int end_cell[2];
		//start = upper right cell, ie: 0,0
		//end = lower left cell, ie: cols.length-1, rows.lenght-1

		//grid mapping out the cell types
		std::vector<std::vector<Cell_Type>> grid;
	};

}
