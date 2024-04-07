#include <iostream>
#include <list>
#include <queue>
#include <regex>
#include <stack>
#include <vector>
#include <string>
#include <sstream>

#include "Map.h"
#include "..\Character\Character.h"
#include "..\Interactable\EmptyCell.h"
#include "..\Interactable\Interactable.h"
#include "..\Item\item.h"
#include "..\Interactable\Wall.h"
#include "..\Door\door.h"

using namespace door;

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
	//creates an empty map
	//will need to initilize all variables explicitly: setRows, setCols, setGrid, setEndCell, setStartCell
}

Map::Map::Map(int r, int c) {
	nextMapID += 1;
	this->mapID = nextMapID;
	this->rows = r;
	this->cols = c;
	//set end cell by default to bottom-right
	this->endCell[0] = r - 1;
	this->endCell[1] = c - 1;
	//set start cell by default to top-left
	this->startCell[0] = 0;
	this->startCell[1] = 0;

	for (int i = 0; i < rows; i++) {
		this->grid.push_back(std::vector<Interactable::Interactable*>(this->cols, new EmptyCell()));
	}
}

void Map::Map::setRows(int rows)
{
	this->rows = rows;
}

void Map::Map::setCols(int cols)
{
	this->cols = cols;
}

void Map::Map::setEndCell(int row, int col) {
	this->endCell[0] = row;
	this->endCell[1] = col;
	//if its the end cell, it has to be empty
	this->setEmpty(row, col);
}

void Map::Map::setStartCell(int row, int col)
{
	this->startCell[0] = row;
	this->startCell[1] = col;
	//if its the starting cell, it has to be empty
	this->setEmpty(row, col);
}

void Map::Map::setGrid() {
	for (int i = 0; i < this->rows; i++) {
		this->grid.push_back(std::vector<Interactable::Interactable*>(this->cols, new EmptyCell()));
	}
}
void Map::Map::setCell(int row, int col, Interactable::Interactable* cell) {

	try {//if you are trying to put an empty cell on the start/end cell
		if ((row == this->startCell[0] && col == this->startCell[1]) || (row == this->endCell[0] && col == this->endCell[1])) {
			throw(1);
		}
		this->grid[row][col] = cell;
	}
	catch (...) {
		std::cout << "Can't change the cell on the starting/ending point." << std::endl;
	}
}

void Map::Map::setEmpty(int row, int col) {

	try {//if you are trying to put an empty cell on the start/end cell
		if ((row == this->startCell[0] && col == this->startCell[1]) || (row == this->endCell[0] && col == this->endCell[1])) {
			throw(1);
		}
		this->grid[row][col] = new EmptyCell();
	}
	catch (...) {
		std::cout << "Can't put an empty cell on the starting/ending point." << std::endl;
	}
}

void Map::Map::setWall(int row, int col) {

	try {//if you are trying to put a wall on the start/end cell
		if ((row == this->startCell[0] && col == this->startCell[1]) || (row == this->endCell[0] && col == this->endCell[1])){
			throw(1);
		}
		this->grid[row][col] = new Wall();
	}
	catch (...) {
		std::cout << "Can't put a wall on the starting/ending point." <<std::endl;
	}
}

void Map::Map::setCharacter(int row, int col, Character::Character* cha) {

	try {//if you are trying to put an empty cell on the start/end cell
		if ((row == this->startCell[0] && col == this->startCell[1]) || (row == this->endCell[0] && col == this->endCell[1])) {
			throw(1);
		}
		this->grid[row][col] = cha;
	}
	catch (...) {
		std::cout << "Can't put a character on the starting/ending point." << std::endl;
	}
}

void Map::Map::setItem(int row, int col, item::Item* item) {

	try {//if you are trying to put an empty cell on the start/end cell
		if ((row == this->startCell[0] && col == this->startCell[1]) || (row == this->endCell[0] && col == this->endCell[1])) {
			throw(1);
		}
		this->grid[row][col] = item;
	}
	catch (...) {
		std::cout << "Can't put an item on the starting/ending point." << std::endl;
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
	//q.push({ 0,0 });
	q.push({ this->startCell[0], this->startCell[1] });
	visited[0][0] = true;

	while (!q.empty()) {
		auto curr = q.front(); // current checking cell
		q.pop();

		//check if reach end cell
		if (curr.first == this->endCell[0] && curr.second == this->endCell[1]) {
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
	return (nextRow >= 0 && nextRow < rows && nextCol >= 0 && nextCol < cols &&
		this->grid[nextRow][nextCol]->serialize()[0] != 'w' &&	!visited[nextRow][nextCol]);
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
	logMessage << "[Map/MoveCharacter] -- " << _targetCharacter->Name() << " is moving to location (" << _targetX - 1 << "," << _targetY - 1 << ") on map " << mapID;
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
			itemcontainer::ItemContainer* itemContainerCell = dynamic_cast<itemcontainer::ItemContainer*>(grid[i][j]);
			Door* doorCell = dynamic_cast<Door*>(grid[i][j]);

			if (characterCell && characterCell->GetIsPlayerControlled()) {
				std::cout << "P ";
			}
			else if (characterCell) {
				std::cout << "N ";
			}
			else if(emptyCell){
				std::cout << "  ";
			}
			else if (wallCell) {
				std::cout <<char(178) << " ";
			}
			else if (itemContainerCell) {
				std::cout << "C ";
			}
			else if (itemCell) {
				std::cout <<char(233) << " ";
			}
			else if (doorCell) {
				std::cout << "D ";
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
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
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

void Map::Map::Print() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			char cell = grid[i][j]->serialize()[0];
			if (i == this->startCell[0] && j == this->startCell[1]) {
				std::cout << "S" << " ";
			}
			else if (i == this->endCell[0] && j == this->endCell[1]) {
				std::cout << "X" << " ";
			}
			else if (cell == 'e') {
				std::cout << "_" << " ";
			}
			else {
				std::cout << cell  << " ";
			}
			std::cout << "| ";
		}
		std::cout << std::endl;
	}
}