#include "Map.h"
#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <queue>
#include <regex>

using namespace std;

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

	string rowInput, colInput;

	regex numRgx("^[1-9][0-9]*$");
	regex answerRgx("[y|n]");
	smatch rowNumMatch, colNumMatch, answerMatch;

	try {
		cout << "Enter the number of rows in your map: ";
		cin >> rowInput;
		if (!regex_match(rowInput, rowNumMatch, numRgx)) {
			throw exception("Invalid input!");
		}

		rows = stoi(rowInput);

		//validate rows input
		while (true) {
			if (cin.fail() || rows < 1) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a positive number: ";
				cin >> rows;
			}
			else {
				break;
			}
		}

		cout << "Enter the number of columns in your map: ";
		cin >> colInput;

		if (!regex_match(colInput, colNumMatch, numRgx)) {
			throw exception("Invalid input!");
		}

		cols = stoi(rowInput);

		//validate columns input
		while (true) {
			if (cin.fail() || cols < 1) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a positive number: ";
				cin >> cols;
			}
			else {
				break;
			}
		}


		Map* map = new Map(rows, cols);
		map->Print();

		string answer;
		cout << "Leave as is? (y/n): ";
		cin >> answer;

		if (!regex_match(answer, answerMatch, answerRgx)) {
			throw exception("Invalid Input!");
		}

		char custm = answer[0];

		while (true) {
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Not a valid answer. Leave the map as is? (y/n): ";
				cin >> custm;
			}
			if (custm == 'y' || custm == 'n') {
				break;
			}
			else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Not a valid answer. Leave the map as is? (y/n): ";
				cin >> custm;
			}
		}

		if (custm == 'n') {
			bool path = false;
			while (!path) {
				// Let the user customize the map how they want
				map->Customize();
				map->Print();
				// Check that there is at least one path from start to end
				cout << "Checking if there is a possible path ... " << endl;
				path = map->IsTherePath();
			}

		}

		return map;
	}
	catch (exception exc) {
		cout << "Invalid input!" << endl;
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
			cout << "Enter the the cell row you want to change: ";
			cin >> row;
			//validate row input
			while (true) {
				if (cin.fail() || row < 0 || row >= rows) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a positive number: ";
					cin >> row;
				}
				else {
					break;
				}
			}

			//Get column input
			cout << "Enter the cell column you want to change: ";
			cin >> col;
			//validate column input
			while (true) {
				if (cin.fail() || col < 0 || col >= cols) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a positive number: ";
					cin >> col;
				}
				else {
					break;
				}
			}

			//if the cell selected is the start or end
			if ((row == 0 && col == 0) || (row == end_cell[0] && col == end_cell[1])) {
				cout << "You cannot change the type of the start or end cell." << endl;
			}
			//valid cell input
			else {
				break;
			}
		}//end row and column input loop

		cout << "Enter the cell type you want to change it to ([e]mpty, [w]all, [s]pecial): ";
		cin >> celltype;
		//validate input
		while (true) {
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Enter only 1 letter please: ";
				cin >> row;
			}
			else {
				break;
			}
		}
		//convert input to celltype
		type = ConvertToCellType(celltype);
		//assign cell to its new type
		grid[row][col] = type;
		//print results
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
		if (!cin.fail()) {
			if (ans == 'y' || ans == 'n') {
				break;
			}
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Not a valid answer.";
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
		cout << "Not a cell type. Defaults to 'empty'.";
		return Cell_Type::empty;
	}

}

bool Map::Map::IsTherePath() {
	// start = 0,0
	// end_cell = {r-1, c-1}
	bool found = false;

	//initial list of visited cells (none to begin with)
	vector<vector<bool>> visited(rows, vector<bool>(cols, false));

	//BFS queue
	queue<pair<int, int>> q;

	//start cell is visited (0,0)
	q.push({ 0,0 });
	visited[0][0] = true;

	while (!q.empty()) {
		auto curr = q.front(); // current checking cell
		q.pop();

		//check if reach end cell
		if (curr.first == end_cell[0] && curr.second == end_cell[1]) {
			//if made it this far, there is a path.
			cout << "There is a path." << endl;
			return true;
		}

		//keep searching
		for (const auto& dir : dirs) {
			int nextRow = curr.first + dir.first;
			int nextCol = curr.second + dir.second;

			//DEBUG: cout << "nextrow: " << nextRow << " nextcol: " << nextCol << endl;

			//check if next cell is not a wall or outside the map or been visited
			if (ValidCell(nextRow, nextCol, visited)) {
				q.push({ nextRow, nextCol });
				visited[nextRow][nextCol] = true;
			}
		}
	}
	cout << "There is no path. Change your map." << endl;
	return false;
}

//validate the next cell
bool Map::Map::ValidCell(int nextRow, int nextCol, vector<vector<bool>> visited) {
	return (nextRow >= 0 && nextRow < rows&& nextCol >= 0 && nextCol < cols&& grid[nextRow][nextCol] != Cell_Type::wall && !visited[nextRow][nextCol]);
}

//print the grid
void Map::Map::Print() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == 0 && j == 0) {
				cout << "O" << " "; //spawn point, ie start
			}
			else if (i == rows - 1 && j == cols - 1) {
				cout << "X" << " "; //end goal
			}
			else {
				cout << static_cast<char>(grid[i][j]) << " ";
			}
		}
		cout << endl;
	}
}

//USE ONLY IN DEBUG
void Map::Map::ChangeCell(int row, int col, Cell_Type type) {
	grid[row][col] = type;
}

