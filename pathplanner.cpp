
#include "Project1.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <stack>
#include <set>
#include <cfloat>
#include <numeric>
using namespace std;


// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
typedef pair<double, pair<int, int> > pPair;

// A structure to hold the neccesary parameters
struct cell {
	int parent_i, parent_j;
	double f, g, h;
};

bool isValid(int row, int col, int r, int c)
{
	
	return (row >= 0) && (row < r) && (col >= 0)
		&& (col < c);
}


bool isUnBlocked(vector<vector<char>> grid, int row, int col)
{
	// Returns true if the cell is not blocked else false
	if (grid[row][col] == 'X')
		return (false);
	else
		return (true);
}


bool isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}

double calculateHValue(vector<vector<char>> grid, int row, int col, Pair dest, int heuristic)
{
	if (heuristic == 1) {
	return (grid[row][col] + ((double)sqrt(
		(row - dest.first) * (row - dest.first)
		+ (col - dest.second) * (col - dest.second))));
} else {
	 return (grid[row][col] + (abs(row - dest.first) + (abs(col - dest.second))));
}
}


void tracePath(vector<vector<char>> grid, vector< vector<cell> > expandedCell, Pair dest, Pair src, set<pPair> openList, 
	vector< vector<bool> > closedList, int mode)
{
//	printf("\nThe Path is ");
	int drow = dest.first;
	int dcol = dest.second;
	int row = dest.first;
	int col = dest.second;

	    if (mode == 2) {
int i,j;
	while (!openList.empty()) {
		pPair p = *openList.begin();


		// Remove this vertex from the open list
		openList.erase(openList.begin());
		i = p.second.first;
		j = p.second.second;
		grid[i][j] = 'c';
	}
}

	for (int i=grid.size()-1;i>=0;i--)
    {
        for (int j = 0; j<grid[0].size(); j++)
        {
            if (closedList[i][j] == 1 && (mode == 1 || mode == 2)) {

            	grid[i][j] = 'o';
            }
        }
    }



	stack<Pair> Path;

	while (!(expandedCell[row][col].parent_i == row
			&& expandedCell[row][col].parent_j == col)) {
		Path.push(make_pair(row, col));
		int temp_row = expandedCell[row][col].parent_i;
		int temp_col = expandedCell[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	Path.push(make_pair(row, col));
	while (!Path.empty()) {
		pair<int, int> p = Path.top();
		Path.pop();
		int temprow = p.first;
		int tempcol = p.second;
		grid[temprow][tempcol] = '+';
	}
	grid[drow][dcol] = 'd';
	int srow = src.first;
	int scol = src.second;
	grid[srow][scol] = 's';
	PrintMap(grid);

	return;
}

// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
void aStarHelper(vector<vector<char>> grid, Pair src, Pair dest, int mode, int heuristic)
{
	int r = grid.size();
	int c = grid[0].size();

	if (isValid(src.first, src.second, r, c) == false) {
		printf("Source is invalid\n");
		return;
	}

	// If the destination is out of range
	if (isValid(src.first, src.second, r, c) == false) {
		printf("Destination is invalid\n");
		return;
	}

	// Either the source or the destination is blocked
	if (isUnBlocked(grid, src.first, src.second) == false
		|| isUnBlocked(grid, dest.first, dest.second)
			== false) {
		printf("Source or the destination is blocked\n");
		return;
	}

	// If the destination cell is the same as source cell
	if (isDestination(src.first, src.second, dest)
		== true) {
		printf("We are already at the destination\n");
		return;
	}

	vector<vector<bool> >  closedList(grid.size(), vector<bool>(grid[0].size()));




	 vector<vector<cell> >  expandedCell(grid.size(), vector<cell>(grid[0].size()));

for (int i = 0; i < grid.size(); i++)
{
    vector<cell> temp;
    for (int j = 0; j < grid[0].size(); j++)
    {
        	expandedCell[i][j].f = FLT_MAX;
			expandedCell[i][j].g = FLT_MAX;
			expandedCell[i][j].h = FLT_MAX;
			expandedCell[i][j].parent_i = -1;
			expandedCell[i][j].parent_j = -1;
    }
}

	int i, j;
	// Initialising the parameters of the starting node
	i = src.first, j = src.second;
	expandedCell[i][j].f = 0.0;
	expandedCell[i][j].g = 0.0;
	expandedCell[i][j].h = 0.0;
	expandedCell[i][j].parent_i = i;
	expandedCell[i][j].parent_j = j;


	set<pPair> openList;

	// Put the starting cell on the open list and set its
	// 'f' as 0
	openList.insert(make_pair(0.0, make_pair(i, j)));

	// We set this boolean value as false as initially
	// the destination is not reached.
	bool foundDest = false;

	while (!openList.empty()) {
		pPair p = *openList.begin();

		// Remove this vertex from the open list
		openList.erase(openList.begin());

		// Add this vertex to the closed list
		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;


		double gNew, hNew, fNew;

		//North

		// Only process this cell if this is a valid one
		if (isValid(i - 1, j, r, c) == true) {
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i - 1, j, dest) == true) {
				// Set the Parent of the destination cell
				expandedCell[i - 1][j].parent_i = i;
				expandedCell[i - 1][j].parent_j = j;
				tracePath(grid, expandedCell, dest, src, openList, closedList, mode);
				foundDest = true;
				return;
			}
			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i - 1][j] == false
					&& isUnBlocked(grid, i - 1, j)
							== true) {
				gNew = expandedCell[i][j].g + 1.0;
				hNew = calculateHValue(grid, i - 1, j, dest, heuristic);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is
				// better, using 'f' cost as the measure.
				if (expandedCell[i - 1][j].f == FLT_MAX
					|| expandedCell[i - 1][j].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i - 1, j)));
					// Update the details of this cell
					expandedCell[i - 1][j].f = fNew;
					expandedCell[i - 1][j].g = gNew;
					expandedCell[i - 1][j].h = hNew;
					expandedCell[i - 1][j].parent_i = i;
					expandedCell[i - 1][j].parent_j = j;
				}
			}
		}

		//South

		// Only process this cell if this is a valid one
		if (isValid(i + 1, j, r, c) == true) {
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i + 1, j, dest) == true) {
				// Set the Parent of the destination cell
				expandedCell[i + 1][j].parent_i = i;
				expandedCell[i + 1][j].parent_j = j;
				tracePath(grid, expandedCell, dest, src, openList, closedList, mode);
				foundDest = true;
				return;
			}
			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i + 1][j] == false
					&& isUnBlocked(grid, i + 1, j)
							== true) {
				gNew = expandedCell[i][j].g + 1.0;
				hNew = calculateHValue(grid, i + 1, j, dest, heuristic);
				fNew = gNew + hNew;


				if (expandedCell[i + 1][j].f == FLT_MAX
					|| expandedCell[i + 1][j].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i + 1, j)));
					expandedCell[i + 1][j].f = fNew;
					expandedCell[i + 1][j].g = gNew;
					expandedCell[i + 1][j].h = hNew;
					expandedCell[i + 1][j].parent_i = i;
					expandedCell[i + 1][j].parent_j = j;
				}
			}
		}

		//----------- 3rd Successor (East) ------------

		// Only process this cell if this is a valid one
		if (isValid(i, j + 1, r, c) == true) {
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i, j + 1, dest) == true) {
				// Set the Parent of the destination cell
				expandedCell[i][j + 1].parent_i = i;
				expandedCell[i][j + 1].parent_j = j;
				tracePath(grid, expandedCell, dest, src, openList, closedList, mode);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i][j + 1] == false
					&& isUnBlocked(grid, i, j + 1)
							== true) {
				gNew = expandedCell[i][j].g + 1.0;
				hNew = calculateHValue(grid, i, j + 1, dest, heuristic);
				fNew = gNew + hNew;


				// better, using 'f' cost as the measure.
				if (expandedCell[i][j + 1].f == FLT_MAX
					|| expandedCell[i][j + 1].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i, j + 1)));
					expandedCell[i][j + 1].f = fNew;
					expandedCell[i][j + 1].g = gNew;
					expandedCell[i][j + 1].h = hNew;
					expandedCell[i][j + 1].parent_i = i;
					expandedCell[i][j + 1].parent_j = j;
				}
			}
		}

		//----------- 4th Successor (West) ------------

		// Only process this cell if this is a valid one
		if (isValid(i, j - 1, r, c) == true) {
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i, j - 1, dest) == true) {
				// Set the Parent of the destination cell
				expandedCell[i][j - 1].parent_i = i;
				expandedCell[i][j - 1].parent_j = j;
				tracePath(grid, expandedCell, dest, src, openList, closedList, mode);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i][j - 1] == false
					&& isUnBlocked(grid, i, j - 1)
							== true) {
				gNew = expandedCell[i][j].g + 1.0;
				hNew = calculateHValue(grid, i, j - 1, dest, heuristic);

				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is
				// better, using 'f' cost as the measure.
				if (expandedCell[i][j - 1].f == FLT_MAX
					|| expandedCell[i][j - 1].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i, j - 1)));
					expandedCell[i][j - 1].f = fNew;
					expandedCell[i][j - 1].g = gNew;
					expandedCell[i][j - 1].h = hNew;
					expandedCell[i][j - 1].parent_i = i;
					expandedCell[i][j - 1].parent_j = j;
				}
			}
		}

		//North-East


		if (isValid(i - 1, j + 1, r, c) == true) {
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i - 1, j + 1, dest) == true) {
				// Set the Parent of the destination cell
				expandedCell[i - 1][j + 1].parent_i = i;
				expandedCell[i - 1][j + 1].parent_j = j;
				tracePath(grid, expandedCell, dest, src, openList, closedList, mode);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i - 1][j + 1] == false
					&& isUnBlocked(grid, i - 1, j + 1)
							== true) {
				gNew = expandedCell[i][j].g + 1.414;
				hNew = calculateHValue(grid, i - 1, j + 1, dest, heuristic);
				fNew = gNew + hNew;


				if (expandedCell[i - 1][j + 1].f == FLT_MAX
					|| expandedCell[i - 1][j + 1].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i - 1, j + 1)));
					expandedCell[i - 1][j + 1].f = fNew;
					expandedCell[i - 1][j + 1].g = gNew;
					expandedCell[i - 1][j + 1].h = hNew;
					expandedCell[i - 1][j + 1].parent_i = i;
					expandedCell[i - 1][j + 1].parent_j = j;
				}
			}
		}

		//North-West



		if (isValid(i - 1, j - 1, r, c) == true) {
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i - 1, j - 1, dest) == true) {
				// Set the Parent of the destination cell
				expandedCell[i - 1][j - 1].parent_i = i;
				expandedCell[i - 1][j - 1].parent_j = j;
				tracePath(grid, expandedCell, dest, src, openList, closedList, mode);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i - 1][j - 1] == false
					&& isUnBlocked(grid, i - 1, j - 1)
							== true) {
				gNew = expandedCell[i][j].g + 1.414;
				hNew = calculateHValue(grid, i - 1, j - 1, dest, heuristic);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is
				// better, using 'f' cost as the measure.
				if (expandedCell[i - 1][j - 1].f == FLT_MAX
					|| expandedCell[i - 1][j - 1].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i - 1, j - 1)));
					expandedCell[i - 1][j - 1].f = fNew;
					expandedCell[i - 1][j - 1].g = gNew;
					expandedCell[i - 1][j - 1].h = hNew;
					expandedCell[i - 1][j - 1].parent_i = i;
					expandedCell[i - 1][j - 1].parent_j = j;
				}
			}
		}

		//South-East
		//------------

		// Only process this cell if this is a valid one
		if (isValid(i + 1, j + 1, r, c) == true) {
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i + 1, j + 1, dest) == true) {
				// Set the Parent of the destination cell
				expandedCell[i + 1][j + 1].parent_i = i;
				expandedCell[i + 1][j + 1].parent_j = j;
				tracePath(grid, expandedCell, dest, src, openList, closedList, mode);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i + 1][j + 1] == false
					&& isUnBlocked(grid, i + 1, j + 1)
							== true) {
				gNew = expandedCell[i][j].g + 1.414;
				hNew = calculateHValue(grid, i + 1, j + 1, dest, heuristic);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is
				// better, using 'f' cost as the measure.
				if (expandedCell[i + 1][j + 1].f == FLT_MAX
					|| expandedCell[i + 1][j + 1].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i + 1, j + 1)));
					expandedCell[i + 1][j + 1].f = fNew;
					expandedCell[i + 1][j + 1].g = gNew;
					expandedCell[i + 1][j + 1].h = hNew;
					expandedCell[i + 1][j + 1].parent_i = i;
					expandedCell[i + 1][j + 1].parent_j = j;
				}
			}
		}

		//----------- 8th Successor (South-West)
		//------------

		// Only process this cell if this is a valid one
		if (isValid(i + 1, j - 1, r, c) == true) {
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i + 1, j - 1, dest) == true) {
				// Set the Parent of the destination cell
				expandedCell[i + 1][j - 1].parent_i = i;
				expandedCell[i + 1][j - 1].parent_j = j;
				tracePath(grid, expandedCell, dest, src, openList, closedList, mode);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i + 1][j - 1] == false
					&& isUnBlocked(grid, i + 1, j - 1)
							== true) {
				gNew = expandedCell[i][j].g + 1.414;
				hNew = calculateHValue(grid, i + 1, j - 1, dest, heuristic);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is
				// better, using 'f' cost as the measure.
				if (expandedCell[i + 1][j - 1].f == FLT_MAX
					|| expandedCell[i + 1][j - 1].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i + 1, j - 1)));
					expandedCell[i + 1][j - 1].f = fNew;
					expandedCell[i + 1][j - 1].g = gNew;
					expandedCell[i + 1][j - 1].h = hNew;
					expandedCell[i + 1][j - 1].parent_i = i;
					expandedCell[i + 1][j - 1].parent_j = j;
				}
			}
		}
	}

	if (foundDest == false)
		printf("Failed to find the Destination Cell\n");

	return;
}




