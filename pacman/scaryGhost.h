#pragma once
#include "gStates.h"
#include "Cell.h"
#include <queue>
#include <vector>
#include <iostream>
#include "CompareCells.h"
#include "pacMan.h"
class gStates;
const int MSZG = 100;
class scaryGhost 
{
private:
	gStates* currentState;
	int x, y; // current position
	int tx, ty; // target

	int numWoods;
	int dx, dy; // motion direction
	bool isMoving, isScard, isDroppingWood;
	std::vector<Cell*> closed;
	std::priority_queue <Cell*, std::vector<Cell*>, CompareCells> open;
	std::priority_queue <Cell*, std::vector<Cell*>, CompareCells>targetLS;
	pacMan* CurrntTarget;
	Cell* CurrntTargetCell;
	const int WALL = 0;
	const int SPACE = 1;
	const int START = 2;
	const int TARGET = 3;
	const int GRAYP = 4;
	const int BLACK = 5;
	const int PATH = 6;
	const int coin = 7;
	const int ghost = 8;
	bool aStar_is_running = true;
	int mazeTemp[MSZG][MSZG] = { 0 };

public:
	scaryGhost();
	scaryGhost(int x, int y, int maze[][MSZG], pacMan* pacMan);
	~scaryGhost();
	gStates* getCurrentState() { return currentState; }
	void setCurrentState(gStates* pNewState) { currentState = pNewState; }
	bool Execute(int mazeTemp[][MSZG]);
	void setIsMoving(bool value) { isMoving = value; }
	void setIsGettingWood(bool value) { isScard = value; }
	void setIsDroppingWood(bool value) { isDroppingWood = value; }
	void setDirection(int targetX, int targetY);
	void RestorePath(Cell* pc);
	void addNeighborASTAR(int row, int col, Cell* pcurrent);
	void RunAStardest();
	int getx() { return x; }
	int gety() { return y; }
	Cell* getCurrntTarget() { return CurrntTargetCell; }
};


