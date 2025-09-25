#pragma once
#include "State.h"
#include "Cell.h"
#include <queue>
#include <vector>
#include <iostream>
#include "CompareCells.h"
#include "reCompareCells.h"
//#include "first.cpp"


class State;

const int MSZ = 100;
//int **mazeP;


class pacMan
{
private:
	State* currentState;
	int x, y; // current position
	int tx, ty; // target
	int gx, gy;
	int numWoods;
	int dx, dy; // motion direction
	bool isMoving, isScard, isDroppingWood;
	std::vector<Cell*> closed;
	std::priority_queue <Cell*, std::vector<Cell*>, CompareCells> open;
	std::priority_queue <Cell*, std::vector<Cell*>, CompareCells> targetLS;
	std::priority_queue <Cell*, std::vector<Cell*>, reCompareCells> fretLS;

	const int WALL = 0;
	const int SPACE = 1;
	const int START = 2;
	const int TARGET = 3;
	const int GRAYP = 4;
	const int BLACK = 5;
	const int PATH = 6;
	const int coin = 7;
	const int ghost = 8;

	std::vector<Cell*> grays;
	bool bfs_is_running = false;
	bool aStar_is_running = true;
	int mazeTemp[MSZ][MSZ] = { 0 }; 
	//int targety=33;
	//int targetx=45;
public:


	pacMan();
	pacMan(int x,int y,int maze[][MSZ]);
	~pacMan();
	State* getCurrentState() { return currentState; }
	void setCurrentState(State* pNewState) { currentState = pNewState; }
	bool Execute(int mazeTemp[][MSZ]);
	void setIsMoving(bool value) { isMoving = value; }
	void setIsGettingWood(bool value) { isScard = value; }
	void setIsDroppingWood(bool value) { isDroppingWood = value; }
	void setDirection(int targetX, int targetY);
	void RestorePath(Cell* pc);
	void addNeighborASTAR(int row, int col, Cell* pcurrent);
	void RunAStardest();
	int getx() { return x; }
	int gety() { return y; }
	Cell* getCurrntTarget() { return targetLS.top(); }
	void CheckNeighbor(int row, int col, Cell* pcurrent);
	void BfsIteration();

};

