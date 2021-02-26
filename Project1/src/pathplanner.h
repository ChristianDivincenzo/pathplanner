
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


typedef pair<int, int> Pair;

typedef pair<double, pair<int, int> > pPair;

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
	int drow = dest.first;
	int dcol = dest.second;
	int row = dest.first;
	int col = dest.second;

	    if (mode == 2) {
int i,j;
	while (!openList.empty()) {
		pPair p = *openList.begin();


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


// Helper for a*
void aStarHelper(vector<vector<char>> grid, Pair src, Pair dest, int mode, int heuristic)
{
	int r = grid.size();
	int c = grid[0].size();

	if (isValid(src.first, src.second, r, c) == false) {
		printf("Source is invalid\n");
		return;
	}

	if (isValid(src.first, src.second, r, c) == false) {
		printf("Destination is invalid\n");
		return;
	}

	if (isUnBlocked(grid, src.first, src.second) == false
		|| isUnBlocked(grid, dest.first, dest.second)
			== false) {
		printf("Source or the destination is blocked\n");
		return;
	}

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
	i = src.first, j = src.second;
	expandedCell[i][j].f = 0.0;
	expandedCell[i][j].g = 0.0;
	expandedCell[i][j].h = 0.0;
	expandedCell[i][j].parent_i = i;
	expandedCell[i][j].parent_j = j;


	set<pPair> openList;


	openList.insert(make_pair(0.0, make_pair(i, j)));

	bool foundDest = false;

	while (!openList.empty()) {
		pPair p = *openList.begin();


		openList.erase(openList.begin());


		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;


		double gNew, hNew, fNew;

		//North

	
		if (isValid(i - 1, j, r, c) == true) {

			if (isDestination(i - 1, j, dest) == true) {

				expandedCell[i - 1][j].parent_i = i;
				expandedCell[i - 1][j].parent_j = j;
				tracePath(grid, expandedCell, dest, src, openList, closedList, mode);
				foundDest = true;
				return;
			}

			else if (closedList[i - 1][j] == false
					&& isUnBlocked(grid, i - 1, j)
							== true) {
				gNew = expandedCell[i][j].g + 1.0;
				hNew = calculateHValue(grid, i - 1, j, dest, heuristic);
				fNew = gNew + hNew;

				if (expandedCell[i - 1][j].f == FLT_MAX
					|| expandedCell[i - 1][j].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i - 1, j)));

					expandedCell[i - 1][j].f = fNew;
					expandedCell[i - 1][j].g = gNew;
					expandedCell[i - 1][j].h = hNew;
					expandedCell[i - 1][j].parent_i = i;
					expandedCell[i - 1][j].parent_j = j;
				}
			}
		}

		//South


		if (isValid(i + 1, j, r, c) == true) {

			if (isDestination(i + 1, j, dest) == true) {
				expandedCell[i + 1][j].parent_i = i;
				expandedCell[i + 1][j].parent_j = j;
				tracePath(grid, expandedCell, dest, src, openList, closedList, mode);
				foundDest = true;
				return;
			}

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

		//(East)

		if (isValid(i, j + 1, r, c) == true) {

			if (isDestination(i, j + 1, dest) == true) {
				expandedCell[i][j + 1].parent_i = i;
				expandedCell[i][j + 1].parent_j = j;
				tracePath(grid, expandedCell, dest, src, openList, closedList, mode);
				foundDest = true;
				return;
			}

			else if (closedList[i][j + 1] == false
					&& isUnBlocked(grid, i, j + 1)
							== true) {
				gNew = expandedCell[i][j].g + 1.0;
				hNew = calculateHValue(grid, i, j + 1, dest, heuristic);
				fNew = gNew + hNew;


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

		// West


		if (isValid(i, j - 1, r, c) == true) {
			if (isDestination(i, j - 1, dest) == true) {

				expandedCell[i][j - 1].parent_i = i;
				expandedCell[i][j - 1].parent_j = j;
				tracePath(grid, expandedCell, dest, src, openList, closedList, mode);
				foundDest = true;
				return;
			}

			else if (closedList[i][j - 1] == false
					&& isUnBlocked(grid, i, j - 1)
							== true) {
				gNew = expandedCell[i][j].g + 1.0;
				hNew = calculateHValue(grid, i, j - 1, dest, heuristic);

				fNew = gNew + hNew;

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

			if (isDestination(i - 1, j + 1, dest) == true) {
				expandedCell[i - 1][j + 1].parent_i = i;
				expandedCell[i - 1][j + 1].parent_j = j;
				tracePath(grid, expandedCell, dest, src, openList, closedList, mode);
				foundDest = true;
				return;
			}


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

			if (isDestination(i - 1, j - 1, dest) == true) {
				// Set the Parent of the destination cell
				expandedCell[i - 1][j - 1].parent_i = i;
				expandedCell[i - 1][j - 1].parent_j = j;
				tracePath(grid, expandedCell, dest, src, openList, closedList, mode);
				foundDest = true;
				return;
			}

			else if (closedList[i - 1][j - 1] == false
					&& isUnBlocked(grid, i - 1, j - 1)
							== true) {
				gNew = expandedCell[i][j].g + 1.414;
				hNew = calculateHValue(grid, i - 1, j - 1, dest, heuristic);
				fNew = gNew + hNew;

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

		if (isValid(i + 1, j + 1, r, c) == true) {

			if (isDestination(i + 1, j + 1, dest) == true) {
				expandedCell[i + 1][j + 1].parent_i = i;
				expandedCell[i + 1][j + 1].parent_j = j;
				tracePath(grid, expandedCell, dest, src, openList, closedList, mode);
				foundDest = true;
				return;
			}


			else if (closedList[i + 1][j + 1] == false
					&& isUnBlocked(grid, i + 1, j + 1)
							== true) {
				gNew = expandedCell[i][j].g + 1.414;
				hNew = calculateHValue(grid, i + 1, j + 1, dest, heuristic);
				fNew = gNew + hNew;

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

		// South-West


		if (isValid(i + 1, j - 1, r, c) == true) {

			if (isDestination(i + 1, j - 1, dest) == true) {

				expandedCell[i + 1][j - 1].parent_i = i;
				expandedCell[i + 1][j - 1].parent_j = j;
				tracePath(grid, expandedCell, dest, src, openList, closedList, mode);
				foundDest = true;
				return;
			}

			else if (closedList[i + 1][j - 1] == false
					&& isUnBlocked(grid, i + 1, j - 1)
							== true) {
				gNew = expandedCell[i][j].g + 1.414;
				hNew = calculateHValue(grid, i + 1, j - 1, dest, heuristic);
				fNew = gNew + hNew;

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




