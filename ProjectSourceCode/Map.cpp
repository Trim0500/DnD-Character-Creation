#include <iostream>
#include <list>
#include <queue>
#include <regex>
#include <stack>
#include <vector>
#include <string>
#include <sstream>

#include "Character.h"
#include "EmptyCell.h"
#include "Interactable.h"
#include "item.h"
#include "Map.h"
#include "Wall.h"

void Map::Map::Notify() {
	for (int i = 0; i < (int)observers.size(); i++)
	{
		observers[i]->update(observerMessage);
	}
}

void Map::Map::CreateObserverMessage(std::string _message = "Empty") {
	observerMessage = _message;
	
	Notify();
}

//default constructor
Map::Map::Map() {
	nextMapID += 1;
	this->mapID = nextMapID;
}

Map::Map::Map(int r, int c) {
	nextMapID += 1;
	this->mapID = nextMapID;
	this->rows = r;
	this->cols = c;
	this->endCell[0] = r - 1;
	this->endCell[1] = c - 1;

	for (int i = 0; i < rows; i++) {
		this->grid.push_back(std::vector<Interactable::Interactable*>(this->cols, new EmptyCell()));
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

//Map::Map* Map::Map::Create() {
//	int rows, cols;
//
//	string rowInput, colInput;
//
//	regex numRgx("^[1-9][0-9]*$");
//	regex answerRgx("[y|n]");
//	smatch rowNumMatch, colNumMatch, answerMatch;
//
//	try {
//		cout << "Enter the number of rows in your map: ";
//		cin >> rowInput;
//		if (!regex_match(rowInput, rowNumMatch, numRgx)) {
//			throw exception("Invalid input!");
//		}
//
//		rows = stoi(rowInput);
//
//		//validate rows input
//		while (true) {
//			if (cin.fail() || rows < 1) {
//				cin.clear();
//				cin.ignore(numeric_limits<streamsize>::max(), '\n');
//				cout << "Invalid input. Please enter a positive number: ";
//				cin >> rows;
//			}
//			else {
//				break;
//			}
//		}
//
//		cout << "Enter the number of columns in your map: ";
//		cin >> colInput;
//
//		if (!regex_match(colInput, colNumMatch, numRgx)) {
//			throw exception("Invalid input!");
//		}
//
//		cols = stoi(rowInput);
//
//		//validate columns input
//		while (true) {
//			if (cin.fail() || cols < 1) {
//				cin.clear();
//				cin.ignore(numeric_limits<streamsize>::max(), '\n');
//				cout << "Invalid input. Please enter a positive number: ";
//				cin >> cols;
//			}
//			else {
//				break;
//			}
//		}
//
//		Map* map = new Map();
//		map->setRows(rows);
//		map->setCols(cols);
//		map->setGrid();
//		map->setEndCell();
//		map->Print();
//
//		string answer;
//		cout << "Leave as is? (y/n): ";
//		cin >> answer;
//
//		if (!regex_match(answer, answerMatch, answerRgx)) {
//			throw exception("Invalid Input!");
//		}
//
//		char custm = answer[0];
//
//		while (true) {
//			if (cin.fail()) {
//				cin.clear();
//				cin.ignore(numeric_limits<streamsize>::max(), '\n');
//				cout << "Not a valid answer. Leave the map as is? (y/n): ";
//				cin >> custm;
//			}
//			if (custm == 'y' || custm == 'n') {
//				break;
//			}
//			else {
//				cin.clear();
//				cin.ignore(numeric_limits<streamsize>::max(), '\n');
//				cout << "Not a valid answer. Leave the map as is? (y/n): ";
//				cin >> custm;
//			}
//		}
//
//		if (custm == 'n') {
//			bool path = false;
//			while (!path) {
//				// Let the user customize the map how they want
//				map->Customize();
//				map->Print();
//				// Check that there is at least one path from start to end
//				cout << "Checking if there is a possible path ... " << endl;
//				path = map->IsTherePath();
//			}
//		}
//
//		return map;
//	}
//	catch (exception exc) {
//		cout << "Invalid input!" << endl;
//	}
//
//}

//void Map::Map::Customize() {
//	bool stop = false;
//	int row;
//	int col;
//	char celltype;
//	//Cell_Type type;
//
//	while (!stop) {
//
//		// get row and column input
//		while (true) {
//			//Get row input
//			cout << "Enter the the cell row you want to change: ";
//			cin >> row;
//			//validate row input
//			while (true) {
//				if (cin.fail() || row < 0 || row >= rows) {
//					cin.clear();
//					cin.ignore(numeric_limits<streamsize>::max(), '\n');
//					cout << "Invalid input. Please enter a positive number: ";
//					cin >> row;
//				}
//				else {
//					break;
//				}
//			}
//
//			//Get column input
//			cout << "Enter the cell column you want to change: ";
//			cin >> col;
//			//validate column input
//			while (true) {
//				if (cin.fail() || col < 0 || col >= cols) {
//					cin.clear();
//					cin.ignore(numeric_limits<streamsize>::max(), '\n');
//					cout << "Invalid input. Please enter a positive number: ";
//					cin >> col;
//				}
//				else {
//					break;
//				}
//			}
//
//			//if the cell selected is the start or end
//			if ((row == 0 && col == 0) || (row == endCell[0] && col == endCell[1])) {
//				cout << "You cannot change the type of the start or end cell." << endl;
//			}
//			//valid cell input
//			else {
//				break;
//			}
//		}//end row and column input loop
//
//		cout << "Enter the cell type you want to change it to ([e]mpty, [w]all, [s]pecial): ";
//		cin >> celltype;
//		//validate input
//		while (true) {
//			if (cin.fail()) {
//				cin.clear();
//				cin.ignore(numeric_limits<streamsize>::max(), '\n');
//				cout << "Invalid input. Enter only 1 letter please: ";
//				cin >> row;
//			}
//			else {
//				break;
//			}
//		}
//		//convert input to celltype
//		type = ConvertToCellType(celltype);
//		//assign cell to its new type
//		grid[row][col] = type;
//		//print results
//		cout << "Your map looks like this: " << endl;
//		Print();
//
//		stop = KeepCustomizing();
//	}
//
//}

//bool Map::Map::KeepCustomizing() {
//	char ans = 'a'; //answer
//	while (true) {
//		cout << "Do you want to keep customizing? (y/n): "; //yes/no
//		cin >> ans;
//		if (!cin.fail()) {
//			if (ans == 'y' || ans == 'n') {
//				break;
//			}
//		}
//		cin.clear();
//		cin.ignore(numeric_limits<streamsize>::max(), '\n');
//		cout << "Not a valid answer.";
//	}
//
//	//doesn't want to stop
//	if (ans == 'y') {
//		return false;
//	}
//	//wants to stop
//	return true;
//}

//convert a given letter to it's corresponding cell type
//Map::Cell_Type Map::ConvertToCellType(char letter) {
//
//	switch (letter) {
//	case 'e':
//		return Cell_Type::empty;
//	case 'w':
//		return Cell_Type::wall;
//	case 's':
//		return Cell_Type::special;
//	default:
//		std::cout << "Not a cell type. Defaults to 'empty'.";
//		return Cell_Type::empty;
//	}

////convert a given letter to it's corresponding cell type
//Map::Cell_Type Map::ConvertToCellType(char letter) {
//
//	switch (letter) {
//	case 'e':
//		return Cell_Type::empty;
//	case 'w':
//		return Cell_Type::wall;
//	case 's':
//		return Cell_Type::special;
//	default:
//		cout << "Not a cell type. Defaults to 'empty'.";
//		return Cell_Type::empty;
//	}
//
//}

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
bool Map::Map::ValidCell(int nextRow, int nextCol, std::vector<std::vector<bool>> visited) {
	return (nextRow >= 0 && nextRow < rows &&
		nextCol >= 0 && nextCol < cols &&
		typeid(grid[nextRow][nextCol]) != typeid(Wall) &&
		!visited[nextRow][nextCol]);
}

void Map::Map::MoveCharacter(const int& _targetX, const int& _targetY, Character::Character* _targetCharacter) {
	// Some logic here to swap character positions based on coordiantes, x and y coor should be 1-indexed

	if (_targetX < 1 || _targetX > grid.size() || _targetY < 1 || _targetY > grid[0].size()) {
		throw std::invalid_argument("[Map/MoveCharacter] -- Invalid coordiantes");
	}

	Interactable::Interactable* valueAtCell = grid[_targetX - 1][_targetY - 1];

	if (!dynamic_cast<EmptyCell*>(valueAtCell)) {
		throw std::invalid_argument("[Map/MoveCharacter] -- Can't move to this cell");
	}

	int sourceLocationX = 0;
	int sourceLocationY = 0;

	for (int i = 0; i < (int)grid.size(); i++)
	{
		for (int j = 0; j < (int)grid[i].size(); j++)
		{
			Interactable::Interactable* currentCellValue = grid[i][j];
			if (_targetCharacter == currentCellValue) {
				sourceLocationX = i;
				sourceLocationY = j;
			}
		}
	}


	Interactable::Interactable* temp = grid[_targetX - 1][_targetY - 1];
	setCell(_targetX - 1, _targetY - 1, _targetCharacter);
	setCell(sourceLocationX, sourceLocationY, temp);

	std::ostringstream logMessage;
	logMessage << "[Map/MoveCharacter] -- " << _targetCharacter->Name() << " is moving to location (" << _targetX << "," << _targetY << ") on map " << mapID;
	CreateObserverMessage(logMessage.str());
}

void Map::Map::printMap()
{
	//print grid col cumbers
	for (int i = 0; i < cols; i++) {
		std::cout<<" " << i << " ";
	}
	std::cout << std::endl;
	//Print top col 
	for (int i = 0; i < cols; i++) {
		std::cout << "___";
		int extraSpaces = i / 10;
		for (int j = 0; j < extraSpaces; j++) {
			std::cout << "_";
		}
	}
	std::cout << std::endl;
	for (int i = 0; i < rows; i++) {

		for (int j = 0; j < cols; j++) {
			//std::cout << "|";
			Character::Character* characterCell = dynamic_cast<Character::Character*>(grid[i][j]);
			EmptyCell* emptyCell = dynamic_cast<EmptyCell*>(grid[i][j]);
			Wall* wallCell = dynamic_cast<Wall*>(grid[i][j]);
			item::Item* itemCell = dynamic_cast<item::Item*>(grid[i][j]);

			if (characterCell) {
				std::cout << "C ";
			}
			else if(emptyCell){
				std::cout << "  ";
			}
			else if (wallCell) {
				std::cout <<char(178) << " ";
			}
			else if (itemCell) {
				std::cout <<char(233) << " ";
			}

			int extraSpaces = j / 10;
			for (int j = 0; j < extraSpaces; j++) {
				std::cout << " ";
			}
			std::cout << "|";
		}
		std::cout << i;
		std::cout << std::endl;
	}
	for (int i = 0; i < cols; i++) {
		std::cout << "---";
		int extraSpaces = i / 10;
		for (int j = 0; j < extraSpaces; j++) {
			std::cout << " ";
		}
	}
	
}

void Map::Map::GetCharacterCoordinates(int& x, int& y, Character::Character* t_character)
{
	int id = t_character->ID();
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			Character::Character* characterCell = dynamic_cast<Character::Character*>(grid[i][j]);
			if (characterCell != nullptr && characterCell->ID() == id) {
				x = i;
				y = j;
				return;
			}
		}
	}
}

std::vector<Character::Character*> Map::Map::GetCharactersInMap() {
	std::vector<Character::Character*> result;
	
	for (int i = 0; i < (int)grid.size(); i++)
	{
		for (int j = 0; j < (int)grid[i].size(); j++)
		{
			Interactable::Interactable* currentCellValue = grid[i][j];
			if (dynamic_cast<Character::Character*>(currentCellValue)) {
				result.push_back(dynamic_cast<Character::Character*>(currentCellValue));
			}
		}
	}

	return result;
}