#include "Character.h"
#include "EmptyCell.h"
#include "Interactable.h"
#include "item.h"
#include "Map.h"
#include "Wall.h"
#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <queue>
#include <regex>

// using namespace std;

//default constructor
Map::Map::Map() {
	nextMapID += 1;
	this->mapID = nextMapID;
}

Map::Map::Map(int r, int c) {
	nextMapID += 1;
	mapID = nextMapID;
	rows = r;
	cols = c;
	endCell[0] = r - 1;
	endCell[1] = c - 1;

	for (int i = 0; i < rows; i++) {
		cellTypeGrid.push_back(std::vector<Cell_Type>(cols, Cell_Type::empty));
	}
}

void Map::Map::setEndCell() {
	this->endCell[0] = this->rows - 1;
	this->endCell[1] = this->cols - 1;
}

void Map::Map::setGrid() {
	for (int i = 0; i < this->rows; i++) {
		this->grid.push_back(std::vector<Interactable::Interactable*>(this->cols, new EmptyCell()));
	}
}
void Map::Map::setCell(int row, int col, Interactable::Interactable* cell) {
	this->grid[row][col] = cell;
}

void Map::Map::setEmpty(int row, int col) {
	this->grid[row][col] = new EmptyCell();
}
void Map::Map::setWall(int row, int col) {
	this->grid[row][col] = new Wall();
}
void Map::Map::setCharacter(int row, int col, Character::Character* cha) {
	this->grid[row][col] = cha;
}
void Map::Map::setItem(int row, int col, item::Item* item) {
	this->grid[row][col] = item;
}

Map::Map* Map::Map::Create() {
	int rows, cols;

	std::string rowInput, colInput;

	std::regex numRgx("^[1-9][0-9]*$");
	std::regex answerRgx("[y|n]");
	std::smatch rowNumMatch, colNumMatch, answerMatch;

	try {
		std::cout << "Enter the number of rows in your map: ";
		std::cin >> rowInput;
		if (!regex_match(rowInput, rowNumMatch, numRgx)) {
			throw std::exception("Invalid input!");
		}

		rows = stoi(rowInput);

		//validate rows input
		while (true) {
			if (std::cin.fail() || rows < 1) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input. Please enter a positive number: ";
				std::cin >> rows;
			}
			else {
				break;
			}
		}

		std::cout << "Enter the number of columns in your map: ";
		std::cin >> colInput;

		if (!regex_match(colInput, colNumMatch, numRgx)) {
			throw std::exception("Invalid input!");
		}

		cols = stoi(rowInput);

		//validate columns input
		while (true) {
			if (std::cin.fail() || cols < 1) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input. Please enter a positive number: ";
				std::cin >> cols;
			}
			else {
				break;
			}
		}

		Map* map = new Map(rows, cols);
		map->Print();

		std::string answer;
		std::cout << "Leave as is? (y/n): ";
		std::cin >> answer;

		if (!regex_match(answer, answerMatch, answerRgx)) {
			throw std::exception("Invalid Input!");
		}

		char custm = answer[0];

		while (true) {
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Not a valid answer. Leave the map as is? (y/n): ";
				std::cin >> custm;
			}
			if (custm == 'y' || custm == 'n') {
				break;
			}
			else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Not a valid answer. Leave the map as is? (y/n): ";
				std::cin >> custm;
			}
		}

		if (custm == 'n') {
			bool path = false;
			while (!path) {
				// Let the user customize the map how they want
				map->Customize();
				map->Print();
				// Check that there is at least one path from start to end
				std::cout << "Checking if there is a possible path ... " << std::endl;
				path = map->IsTherePath();
			}
		}

		return map;
	}
	catch (std::exception exc) {
		std::cout << "Invalid input!" << std::endl;
	}

}

void Map::Map::Customize() {
	bool stop = false;
	int row;
	int col;
	char celltype;
	Cell_Type type;

	while (!stop) {

		// get row and column input
		while (true) {
			//Get row input
			std::cout << "Enter the the cell row you want to change: ";
			std::cin >> row;
			//validate row input
			while (true) {
				if (std::cin.fail() || row < 0 || row >= rows) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Invalid input. Please enter a positive number: ";
					std::cin >> row;
				}
				else {
					break;
				}
			}

			//Get column input
			std::cout << "Enter the cell column you want to change: ";
			std::cin >> col;
			//validate column input
			while (true) {
				if (std::cin.fail() || col < 0 || col >= cols) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Invalid input. Please enter a positive number: ";
					std::cin >> col;
				}
				else {
					break;
				}
			}

			//if the cell selected is the start or end
			if ((row == 0 && col == 0) || (row == endCell[0] && col == endCell[1])) {
				std::cout << "You cannot change the type of the start or end cell." << std::endl;
			}
			//valid cell input
			else {
				break;
			}
		}//end row and column input loop

		std::cout << "Enter the cell type you want to change it to ([e]mpty, [w]all, [s]pecial): ";
		std::cin >> celltype;
		//validate input
		while (true) {
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input. Enter only 1 letter please: ";
				std::cin >> row;
			}
			else {
				break;
			}
		}
		//convert input to celltype
		type = ConvertToCellType(celltype);
		//assign cell to its new type
		cellTypeGrid[row][col] = type;
		//print results
		std::cout << "Your map looks like this: " << std::endl;
		Print();

		stop = KeepCustomizing();
	}

}

bool Map::Map::KeepCustomizing() {
	char ans = 'a'; //answer
	while (true) {
		std::cout << "Do you want to keep customizing? (y/n): "; //yes/no
		std::cin >> ans;
		if (!std::cin.fail()) {
			if (ans == 'y' || ans == 'n') {
				break;
			}
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Not a valid answer.";
	}

	//doesn't want to stop
	if (ans == 'y') {
		return false;
	}
	//wants to stop
	return true;
}


//convert a given letter to it's corresponding cell type
Map::Cell_Type Map::ConvertToCellType(char letter) {

	switch (letter) {
	case 'e':
		return Cell_Type::empty;
	case 'w':
		return Cell_Type::wall;
	case 's':
		return Cell_Type::special;
	default:
		std::cout << "Not a cell type. Defaults to 'empty'.";
		return Cell_Type::empty;
	}

}

bool Map::Map::IsTherePath() {
	// start = 0,0
	// end_cell = {r-1, c-1}
	bool found = false;

	//initial list of visited cells (none to begin with)
	std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

	//BFS queue
	std::queue<std::pair<int, int>> q;

	//start cell is visited (0,0)
	q.push({ 0,0 });
	visited[0][0] = true;

	while (!q.empty()) {
		auto curr = q.front(); // current checking cell
		q.pop();

		//check if reach end cell
		if (curr.first == endCell[0] && curr.second == endCell[1]) {
			//if made it this far, there is a path.
			std::cout << "There is a path." << std::endl;
			return true;
		}

		//keep searching
		for (const auto& dir : dirs) {
			int nextRow = curr.first + dir.first;
			int nextCol = curr.second + dir.second;

			//DEBUG: std::cout << "nextrow: " << nextRow << " nextcol: " << nextCol << std::endl;

			//check if next cell is not a wall or outside the map or been visited
			if (ValidCell(nextRow, nextCol, visited)) {
				q.push({ nextRow, nextCol });
				visited[nextRow][nextCol] = true;
			}
		}
	}
	std::cout << "There is no path. Change your map." << std::endl;
	return false;
}

//validate the next cell
bool Map::Map::ValidCellInteractable(int nextRow, int nextCol, std::vector<std::vector<bool>> visited) {
	return (nextRow >= 0 && nextRow < rows &&
		nextCol >= 0 && nextCol < cols &&
		typeid(grid[nextRow][nextCol]) != typeid(Wall) &&
		!visited[nextRow][nextCol]);
}

bool Map::Map::ValidCell(int nextRow, int nextCol, std::vector<std::vector<bool>> visited) {
	return (nextRow >= 0 && nextRow < rows &&
		nextCol >= 0 && nextCol < cols &&
		cellTypeGrid[nextRow][nextCol] != Cell_Type::wall &&
		!visited[nextRow][nextCol]);
}

//print the grid
void Map::Map::Print() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == 0 && j == 0) {
				std::cout << "O" << " "; //spawn point, ie start
			}
			else if (i == rows - 1 && j == cols - 1) {
				std::cout << "X" << " "; //end goal
			}
			else {
				std::cout << static_cast<char>(cellTypeGrid[i][j]) << " ";
			}
		}
		std::cout << std::endl;
	}
}

//USE ONLY IN DEBUG
void Map::Map::ChangeCell(int row, int col, Cell_Type type) {
	cellTypeGrid[row][col] = type;
}

