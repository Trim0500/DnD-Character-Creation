#include "Character.h"
#include "EmptyCell.h"
#include "Interactable.h"
#include "item.h"
#include "Map.h"
#include "Wall.h"
#include <iostream>
#include <list>
#include <queue>
#include <regex>
#include <stack>
#include <vector>

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
}

void Map::Map::setStartCell(int row, int col)
{
	this->startCell[0] = row;
	this->startCell[1] = col;
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


