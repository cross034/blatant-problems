#include<iostream>
#include<vector>
#include<list>
#include"PuzzleState.h"

bool existsInList(std::list<PuzzleState*> stateList, const PuzzleState* state)
{
	for (std::list<PuzzleState*>::iterator it = stateList.begin(); it != stateList.end(); it++)
	{
		if (**it == *state)
			return true;
	}
	return false;
}

std::list<PuzzleState*>::iterator getFromList(std::list<PuzzleState*> stateList, const PuzzleState* state)
{
	for (std::list<PuzzleState*>::iterator it = stateList.begin(); it != stateList.end(); it++)
	{
		if (**it == *state)
			return it;
	}
}

void insertInList(std::list<PuzzleState*>& stateList, PuzzleState* state)
{
	for (std::list<PuzzleState*>::iterator it = stateList.begin(); ; it++)
	{
		if (it == stateList.end())
		{
			stateList.push_back(state);
			break;
		}
		if ((*it)->f >= state->f)
		{
			if ((*it)->f == state->f)
				it++;
			stateList.insert(it, state);
			break;
		}
	}
}

int main()
{
	int initBoard[3][3]{ 
		{0, 1, 2}, 
		{8, 7, 3}, 
		{4, 6, 5} };

	int finalBoard[3][3]{ 
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 0} };

	std::list<PuzzleState*> open;
	std::list<PuzzleState*> visited;

	PuzzleState::setFinalBoard(finalBoard);
	PuzzleState initState(initBoard);

	open.push_back(&initState);

	while (!open.empty())
	{
		PuzzleState *currentState = open.front();
		open.pop_front();
		visited.push_back(currentState);
		if (currentState->h != 0)
		{
			std::vector<PuzzleState::Direction> directions = currentState->getPossibleDirections();

			for (PuzzleState::Direction direction : directions)
			{
				PuzzleState *nextState = currentState->createNextState(direction);

				if (existsInList(visited, nextState))
					continue;
				if (existsInList(open, nextState))
				{
					std::list<PuzzleState*>::iterator openIter = getFromList(open, nextState);
					if ((*openIter)->f > nextState->f)
						open.erase(openIter);
					else
						continue;
				}
				insertInList(open, nextState);
			}
		}
		else
		{
			break;
		}
	}

	PuzzleState *state = visited.back();
	std::list<PuzzleState*> finalStates;
	finalStates.push_back(state);

	while (state->previousState != nullptr)
	{
		state = state->previousState;
		//state->printBoard();
		finalStates.push_back(state);
	}
	for (std::list<PuzzleState*>::reverse_iterator it = finalStates.rbegin(); it != finalStates.rend(); it++)
	{
		(*it)->printBoard();
	}
	printf("Total visited : %zd \n", visited.size());
	printf("Total open : %zd \n", open.size());

	std::cin.get();
}