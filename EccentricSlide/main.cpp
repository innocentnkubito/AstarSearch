
// Name : INNOCENT NKUBITO

#include <iostream>
#include<string>
#include<cstdlib>

const int LENGTH = 3;
using namespace std;

struct nextLevel   // This struct represents the next level of states derived from a given state
{                  // A given state can have at most 4 next nodes derived from it.
	// A next node has one more string that indicates the direction
	string nextState1[LENGTH + 1], nextState2[LENGTH + 1], nextState3[LENGTH + 1], nextState4[LENGTH + 1];
	// +1 indicates direction
};

bool compareStates(string state1[], string state2[]); // This function checks if two states are the same
void copyState(string state1[], string state2[]);  // This function copies state1 into state2
void getPosition(string state[], char element, int& row, int& column); // returns the position of a tile
int deriveStates(string state[], struct nextLevel & level); // derive the next level of states from a state
void swapTileSpace(string state[], int row, int col, int tileRow, int tileCol, string tileDirection);
int manhattanCost(string state[], string goalState[]); // returns the manhattan cost of a state
void findCosts(struct nextLevel& level, int numOfStates, string previousState[], string goalState[], int g, int costs[]);
int findMinCost(int costs[]); // returns the next node with the minimum cost

int main(int argc, const char * argv[])
{
	string input, output;
	string goal[LENGTH], current[LENGTH], previous[LENGTH]; // a state is represented by a string array

	cout << " Enter initial state and goal state :" << endl; // getting user input
	for (int i = 0; i < LENGTH * 2; i++)
	{
		cin >> input;
		if (i<3)
			current[i] = input;
		else
			goal[i % 3] = input;
	}

	int g = 0;  // The cost it took to get to this level
	copyState(current, previous); // initializing previous state
	output = "";
	while (!compareStates(current, goal))  // while the current state is not the goal state
	{
		// generate all the possible next states
		struct nextLevel level;
		int costs[4];  // Cost associated with at most 4 possible next states
		int numOfStates = deriveStates(current, level); // number of states in the next level of states
		g++;
		findCosts(level, numOfStates, previous, goal, g, costs);
		int minState = findMinCost(costs); // next state with minimum cost
		switch (minState)
		{
		case 1:
			copyState(current, previous);
			copyState(level.nextState1, current);
			output += level.nextState1[LENGTH];
			break;
		case 2:
			copyState(current, previous);
			copyState(level.nextState2, current);
			output += level.nextState2[LENGTH];
			break;
		case 3:
			copyState(current, previous);
			copyState(level.nextState3, current);
			output += level.nextState3[LENGTH];
			break;
		case 4:
			copyState(current, previous);
			copyState(level.nextState4, current);
			output += level.nextState4[LENGTH];
			break;
		}
	}

	cout << endl << output << endl << endl;
	return 0;
}

bool compareStates(string state1[], string state2[]) // returns true if the two states are the same
{
	bool same = true;
	for (int i = 0; i<LENGTH; i++)
	if (state1[i] != state2[i])
	{
		same = false;
		break;
	}
	return same;
}
void copyState(string state1[], string state2[]) // copies state 1 into state 2
{
	for (int i = 0; i < LENGTH; i++)
		state2[i] = state1[i];
}
void getPosition(string state[], char element, int& row, int& column)
{
	for (int i = 0; i<LENGTH; i++)
	for (int j = 0; j<LENGTH; j++)
	if (state[i][j] == element)
	{
		row = i;
		column = j;
		break;
	}
}

void swapTileSpace(string state[], int row, int col, int tileRow, int tileCol, string tileDirection)
{
	state[row][col] = state[tileRow][tileCol];
	state[tileRow][tileCol] = 'X';
	state[LENGTH] = tileDirection; // last element in the next state is the direction of the tile
}

int deriveStates(string state[], struct nextLevel & level)
{
	// This function returns the next states derived from a given state
	// It also returns the number of states that were derived from a given state

	int number = 0;
	int row, col;
	copyState(state, level.nextState1); // initializing the next nodes, a given state can have at most
	copyState(state, level.nextState2);  // 4 next derived states.
	copyState(state, level.nextState3);
	copyState(state, level.nextState4);

	getPosition(state, 'X', row, col); // find the position of the space

	if (row == 0 && col == 0)
	{
		number = 2;
		swapTileSpace(level.nextState1, row, col, 0, 1, "L");
		swapTileSpace(level.nextState2, row, col, 1, 0, "U");
	}
	else if (row == 0 && col == 1)
	{
		number = 3;
		swapTileSpace(level.nextState1, row, col, 0, 0, "R");
		swapTileSpace(level.nextState2, row, col, 0, 2, "L");
		swapTileSpace(level.nextState3, row, col, 1, 1, "U");
	}
	else if (row == 0 && col == 2)
	{
		number = 2;
		swapTileSpace(level.nextState1, row, col, 0, 1, "R");
		swapTileSpace(level.nextState2, row, col, 1, 2, "U");
	}
	else if (row == 1 && col == 0)
	{
		number = 3;
		swapTileSpace(level.nextState1, row, col, 0, 0, "D");
		swapTileSpace(level.nextState2, row, col, 2, 0, "U");
		swapTileSpace(level.nextState3, row, col, 1, 1, "L");
	}
	else if (row == 1 && col == 1)
	{
		number = 4;
		swapTileSpace(level.nextState1, row, col, 1, 0, "R");
		swapTileSpace(level.nextState2, row, col, 0, 1, "D");
		swapTileSpace(level.nextState3, row, col, 2, 1, "U");
		swapTileSpace(level.nextState4, row, col, 1, 2, "L");
	}
	else if (row == 1 && col == 2)
	{
		number = 3;
		swapTileSpace(level.nextState1, row, col, 1, 1, "R");
		swapTileSpace(level.nextState2, row, col, 0, 2, "D");
		swapTileSpace(level.nextState3, row, col, 2, 2, "U");
	}
	else if (row == 2 && col == 0)
	{
		number = 2;
		swapTileSpace(level.nextState1, row, col, 1, 0, "D");
		swapTileSpace(level.nextState2, row, col, 2, 1, "L");
	}
	else if (row == 2 && col == 1)
	{
		number = 3;
		swapTileSpace(level.nextState1, row, col, 2, 0, "R");
		swapTileSpace(level.nextState2, row, col, 1, 1, "D");
		swapTileSpace(level.nextState3, row, col, 2, 2, "L");
	}
	else if (row == 2 && col == 2)
	{
		number = 2;
		swapTileSpace(level.nextState1, row, col, 2, 1, "R");
		swapTileSpace(level.nextState2, row, col, 1, 2, "D");
	}
	return number;
}

int manhattanCost(string state[], string goalState[]) // returns the manhattan cost of a state
{
	int cost = 0;
	for (int i = 0; i<LENGTH; i++)
	for (int j = 0; j<LENGTH; j++)
	if (state[i][j] != 'X')
	{
		int row, col;
		getPosition(goalState, state[i][j], row, col);
		cost += abs(i - row) + abs(j - col);
	}

	return cost;
}

void findCosts(struct nextLevel& level, int numOfStates, string previousState[], string goalState[], int g, int costs[])
{
	// This function finds the cost associated with all the possible next states of a state
	for (int i = 0; i<4; i++)  // initializing the costs to an invalid cost
		costs[i] = -1;

	switch (numOfStates)
	{
	case 2:
		if (!compareStates(previousState, level.nextState1))
			costs[0] = manhattanCost(level.nextState1, goalState) + g;

		if (!compareStates(previousState, level.nextState2))
			costs[1] = manhattanCost(level.nextState2, goalState) + g;
		break;

	case 3:
		if (!compareStates(previousState, level.nextState1))
			costs[0] = manhattanCost(level.nextState1, goalState) + g;

		if (!compareStates(previousState, level.nextState2))
			costs[1] = manhattanCost(level.nextState2, goalState) + g;

		if (!compareStates(previousState, level.nextState3))
			costs[2] = manhattanCost(level.nextState3, goalState) + g;
		break;

	case 4:
		if (!compareStates(previousState, level.nextState1))
			costs[0] = manhattanCost(level.nextState1, goalState) + g;

		if (!compareStates(previousState, level.nextState2))
			costs[1] = manhattanCost(level.nextState2, goalState) + g;

		if (!compareStates(previousState, level.nextState3))
			costs[2] = manhattanCost(level.nextState3, goalState) + g;

		if (!compareStates(previousState, level.nextState4))
			costs[3] = manhattanCost(level.nextState4, goalState) + g;
		break;
	}
}

int findMinCost(int costs[])  // returns the state that has the minimum cost
{
	int minCost = 0;
	int state = 0;  // the next state that has  the minimum cost
	for (int i = 0; i<4; i++)  // initializing minCost
	if (costs[i] != -1)
	{
		minCost = costs[i];
		state = i;
		break;
	}

	for (int i = 0; i<4; i++)
	if (costs[i] != -1 && costs[i] < minCost)
	{
		minCost = costs[i];
		state = i;
		break;
	}

	return state + 1;  // add 1 because states start from 1, not 0
}













