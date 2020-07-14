#include"PuzzleState.h"

int PuzzleState::m_finalBoard[3][3];

void PuzzleState::copyBoard(int(&toBoard)[3][3],const int fromBoard[3][3])
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			toBoard[r][c] = fromBoard[r][c];
		}
	}
}

int PuzzleState::getDistance()
{
	int distance = 0;
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (m_board[r][c] != m_finalBoard[r][c])
			{
				distance += 1;
			}
		}
	}
	return distance;
}

void PuzzleState::findBlankSpace()
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (m_board[r][c] == 0)
			{
				blankR = r;
				blankC = c;
			}
		}
	}
}

void PuzzleState::swapValue(int R1, int C1, int R2, int C2)
{
	int temp = m_board[R2][C2];
	m_board[R2][C2] = m_board[R1][C1];
	m_board[R1][C1] = temp;
}

void PuzzleState::moveBlank(Direction direction)
{
	if (direction == Left)
	{
		swapValue(blankR, blankC, blankR, blankC - 1);
		blankC -= 1;
	}
	if (direction == Right)
	{
		swapValue(blankR, blankC, blankR, blankC + 1);
		blankC += 1;
	}
	if (direction == Up)
	{
		swapValue(blankR, blankC, blankR - 1, blankC);
		blankR -= 1;
	}
	if (direction == Down)
	{
		swapValue(blankR, blankC, blankR + 1, blankC);
		blankR += 1;
	}
}

bool PuzzleState::operator==(const PuzzleState& otherBoard)
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (m_board[r][c] != otherBoard.m_board[r][c])
				return false;
		}
	}
	return true;
}

void PuzzleState::setFinalBoard(int otherBoard[3][3])
{
	copyBoard(m_finalBoard, otherBoard);
}

PuzzleState::PuzzleState(int initBoard[3][3])
{
	copyBoard(m_board, initBoard);
	lastMoveDirection = PuzzleState::None;
	g = 0;
	h = getDistance();
	this->f = g + h;
	findBlankSpace();
	previousState = nullptr;
}

PuzzleState::PuzzleState(PuzzleState* otherState)
{
	copyBoard(m_board, otherState->m_board);
	blankR = otherState->blankR;
	blankC = otherState->blankC;
	previousState = otherState;
}

void PuzzleState::printBoard()
{
	std::cout  << " ----------- " << std::endl;
	for (int r = 0; r < 3; r++)
	{
		std::cout << "| ";
		for (int c = 0; c < 3; c++)
		{
			if (m_board[r][c] == 0)
				std::cout << " ";
			else
			{
				std::cout << m_board[r][c];
			}
			std::cout << " | ";
		}
		std::cout << std::endl << " ----------- " << std::endl;
	}
	printf(" g:%d h:%d f:%d \n\n", g, h, f);
	//std::cout << g << " " << h << " " << f << std::endl << std::endl;
}

std::vector<PuzzleState::Direction> PuzzleState::getPossibleDirections()
{
	std::vector<Direction> directions;
	if (blankR > 0 && lastMoveDirection != Down)
		directions.push_back(Up);
	if (blankR < 2 && lastMoveDirection != Up)
		directions.push_back(Down);
	if (blankC > 0 && lastMoveDirection != Right)
		directions.push_back(Left);
	if (blankC < 2 && lastMoveDirection != Left)
		directions.push_back(Right);

	return directions;
}

PuzzleState* PuzzleState::createNextState(Direction direction)
{
	PuzzleState* nextState = new PuzzleState(this);
	nextState->lastMoveDirection = direction;
	nextState->moveBlank(direction);
	nextState->g = g + 1;
	nextState->h = nextState->getDistance();
	nextState->f = nextState->g + nextState->h;
	return nextState;
}