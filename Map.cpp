#include "Map.h"
#include <iostream>
#include <vector>

//basic constructor
Map::Map::Map(int r, int c) {
	rows = r;
	cols = c;

	//grid.resize(rows); // resize how many rows

	for (int i = 0; i < rows; i++) {
		grid.push_back(vector<Cell_Type>(cols, Cell_Type::empty));
	}

	/*push back every row to have proper amount of cols
	for (int i = 0; i < rows; i++) {
		grid[i].resize(cols, empty);
	}*/

	/*for (int i = 0; i < Rows(); i++) {
		for (int j = 0; j < Cols(); j++) {
			grid[i][j] = empty;
		}
	}*/
}

Map::Map* Map::Map::Create() {
	int rows, cols;

	cout << "Enter the number of rows in your map: ";
	cin >> rows;
	cout << "Enter the number of columns in your map: ";
	cin >> cols;

	Map* map = new Map(rows, cols);

	map->Customize();

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
		cout << "Enter the cell type you want to change it to (e, w, i): ";
		cin >> celltype;

		type = ConvertToCellType(celltype);

		this->grid[row][col] = type;

		cout << "Your map looks like this: " << endl;
		this->Print();

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
	case 'i':
		return Cell_Type::item;
	default:
		cout << "Not a cell type. Defaults to 'empty'.";
		return Cell_Type::empty;
	}

}

//print the grid
void Map::Map::Print() {
	for (int i = 0; i < Rows(); i++) {
		for (int j = 0; j < Cols(); j++) {
			cout << static_cast<char>(grid[i][j]) << " ";
		}
		cout << endl;
	}
}
