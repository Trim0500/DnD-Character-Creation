#include "Map.h"
#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <queue>

//basic constructor
Map::Map::Map(int r, int c) {
	rows = r;
	cols = c;
	end_cell[0] = r - 1;
	end_cell[1] = c - 1;

	for (int i = 0; i < rows; i++) {
		grid.push_back(vector<Cell_Type>(cols, Cell_Type::empty));
	}
}

Map::Map* Map::Map::Create() {
	int rows, cols;

	cout << "Enter the number of rows in your map: ";
	cin >> rows;
	cout << "Enter the number of columns in your map: ";
	cin >> cols;

	Map* map = new Map(rows, cols);

	map->Customize();
	map->Print();
	cout << "check path" << endl;
	bool path = map->IsTherePath();
	cout << path;

	return map;
}

void Map::Map::Customize() {
	bool stop = false;
	int row;
	int col;
	char celltype;
	Cell_Type type;

	while (!stop) {
		cout << "Enter the the cell row you want to change: ";
		cin >> row;
		cout << "Enter the cell column you want to change: ";
		cin >> col;
		cout << "Enter the cell type you want to change it to (e, w, s): ";
		cin >> celltype;

		type = ConvertToCellType(celltype);

		grid[row][col] = type;

		cout << "Your map looks like this: " << endl;
		Print();

		stop = KeepCustomizing();

	}

}

bool Map::Map::KeepCustomizing() {
	char ans = 'a'; //answer
	while (true) {
		cout << "Do you want to keep customizing? (y/n): "; //yes/no
		cin >> ans;
		if (ans == 'y' || ans == 'n') {
			break;
		}
		cout << "Not a valid answer.";
	}
	//don't wants to stop
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
		cout << "Not a cell type. Defaults to 'empty'.";
		return Cell_Type::empty;
	}

}

bool Map::Map::IsTherePath() {
	// start = 0,0
	// end = lower right cell, ie: cols.length-1, rows.lenght-1
	//int curr[2] = { 0,0 }; //current checking cell
	//end_cell = {r-1, c-1}
	bool found = false;

	//initial list of visited cells (none to begin with)
	vector<vector<bool>> visited(rows, std::vector<bool>(cols, false));

	//BFS queue
	queue<pair<int, int>> q;

	//start cell is visited (0,0)
	q.push({ 0,0 });
	visited[0][0] = true;
	cout << "initial values" << endl;

	while (!q.empty()) {
		auto curr = q.front(); // current checking cell
		q.pop();

		cout << "checking: " << curr.first << ", " << curr.second << endl;

		//check if at the end cell
		if (curr.first == end_cell[0] && curr.second == end_cell[1]) {
			cout << "almost done" << endl;
			return true;
		}

		//keep searching
		for (const auto& dir : dirs) {
			cout << "keep searching" << endl;
			int nextRow = curr.first + dir.first;
			int nextCol = curr.second + dir.second;

			cout << "nextrow: " << nextRow << " nextcol: " << nextCol << endl;

			//check if next cell is not a wall or outside the map or been visited
			if (ValidCell(nextRow, nextCol, visited) {
				q.push({ nextRow, nextCol });
				visited[nextRow][nextCol] = true;
				visited[nextRow][nextCol] = true;
			}
		}
	}

	return false;

}

bool Map::Map::ValidCell(int nextRow, int nextCol, vector<vector<bool>> visited) {
	return (nextRow >= 0 && nextRow < rows && nextCol >= 0 && nextCol < cols && grid[nextRow][nextCol] == Cell_Type::empty && !visited[nextRow][nextCol]);
}

//print the grid
void Map::Map::Print() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << static_cast<char>(grid[i][j]) << " ";
		}
		cout << endl;
	}
}
