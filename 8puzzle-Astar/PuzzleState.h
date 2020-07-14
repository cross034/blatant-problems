#pragma once

#include<iostream>
#include<vector>

class PuzzleState
{
private:
	static int m_finalBoard[3][3];

	int blankR, blankC;

public:
	enum Direction { Left, Right, Up, Down, None };
	int m_board[3][3];
	int g, h, f;
	Direction lastMoveDirection;
	PuzzleState *previousState;

private:
	static void copyBoard(int(&toBoard)[3][3], const int fromBoard[3][3]);

	int getDistance();

	void findBlankSpace();

	void swapValue(int R1, int C1, int R2, int C2);

	void moveBlank(Direction direction);

public:
	bool operator==(const PuzzleState& otherBoard);

	static void setFinalBoard(int otherBoard[3][3]);

	PuzzleState(int initBoard[3][3]);

	PuzzleState(PuzzleState* otherState);

	void printBoard();

	std::vector<Direction> getPossibleDirections();

	PuzzleState* createNextState(Direction direction);
};