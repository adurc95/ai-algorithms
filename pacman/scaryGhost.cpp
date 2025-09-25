#include "scaryGhost.h"
#include "pacMan.h"
#include "gHunt.h"
#include "GLUT.H"
#include <math.h>




scaryGhost::scaryGhost()
{

}

scaryGhost::scaryGhost(int xc, int yc, int maze[][MSZG], pacMan* pacMan)
{
	mazeTemp[yc][xc] = ghost;
	maze[yc][xc] = ghost;

	isMoving = false;
	isScard = false;
	isDroppingWood = false;
	numWoods = 0;
	x = xc;
	y = yc;
	dy = y;
	dx = x;
	CurrntTarget = pacMan;
	currentState = new gHunt();
	//currentState->OnStateEnter(this);


}

scaryGhost::~scaryGhost()
{
}


bool scaryGhost::Execute(int maze[][MSZG])
{


	double dist;
	// if the flag isMoving true then move player
	if (isMoving)
	{
		maze[y][x] = SPACE;
		y = dy;
		x = dx;
		if (maze[y][x] == 2) {
			std::cout << "pacman loss!!!!!!!!!!!!!!!!!!!!!\n";
			return true;
		}
		maze[y][x] = ghost;


	}
	


	while (!open.empty()) {        //check whether pq empty or not
		open.pop();                 //erasing content one by one
		//cout << m.maths << ' ' << m.english << endl;
	}
	aStar_is_running = true;
	for (int t = 0; t < MSZG; t++)
	{
		for (int k = 0; k < MSZG; k++)
		{
			mazeTemp[t][k] = maze[t][k];
		}
	}
	Cell* pc = new Cell(y, x, abs(y - CurrntTarget->gety()) + abs(x - CurrntTarget->getx()));
	open.push(pc);
	CurrntTargetCell = new Cell(CurrntTarget->gety(), CurrntTarget->getx(), abs(y - CurrntTarget->gety()) + abs(x - CurrntTarget->getx()));
	targetLS.push(CurrntTargetCell);
	currentState->OnStateEnter(this);
	return false;
	//setDirection(targetx, targety);
}

void scaryGhost::setDirection(int targetY, int targetX)
{//chenge to astar
	mazeTemp[targetY][targetX] = TARGET;
	while (aStar_is_running)
		RunAStardest();
}
void scaryGhost::RestorePath(Cell* pc)
{

	//if (pc->getG() != 0) {
	while (pc->getG() > 1)
	{
		//mazeTemp[pc->getRow()][pc->getCol()] = PATH;
		pc = pc->getParent();
	}
	//}

	dy = pc->getRow();
	dx = pc->getCol();
}

void scaryGhost::addNeighborASTAR(int row, int col, Cell* pcurrent)
{
	Cell* pneighbor;
	// is mazeTemp[row][col] a TARGET
	if ((mazeTemp[row][col] == TARGET))
	{
		//std::cout << "the solution has been found in player\n";
		aStar_is_running = false;
		if (pcurrent->getParent() != nullptr)
			RestorePath(pcurrent);
		else {
			dy = row;
			dx = col;
		}
	}
	else if (mazeTemp[row][col] == WALL || mazeTemp[row][col] == BLACK) {
		return;
	}
	else // this is white neighbor
	{
		Cell* bastTarget = CurrntTargetCell;

		int h = abs(col - bastTarget->getRow()) + abs(row - bastTarget->getCol());
		int f = h;

		pneighbor = new Cell(row, col, pcurrent, f, pcurrent->getG());
		mazeTemp[row][col] = GRAYP;

		open.push(pneighbor);


	}
}
void scaryGhost::RunAStardest()
{
	Cell* pcurrent;
	int r, c;
	//int successorNum = 0;
	if (open.empty())
	{
		//std::cout << "There is no solution in player\n";
		aStar_is_running = false;
		return;
	}
	else // grays is not empty
	{
		pcurrent = open.top();

		// remove pcurrent from grays and paint it black
		open.pop();
		r = pcurrent->getRow();
		c = pcurrent->getCol();
		closed.push_back(pcurrent);

		mazeTemp[r][c] = BLACK;
		if (mazeTemp[r + 1][c] == SPACE || mazeTemp[r + 1][c] == TARGET) {
			addNeighborASTAR(r + 1, c, pcurrent);

		}

		// down
		if (aStar_is_running && (mazeTemp[r - 1][c] == SPACE || mazeTemp[r - 1][c] == TARGET)) {
			addNeighborASTAR(r - 1, c, pcurrent);


		}
		// left
		if (aStar_is_running && (mazeTemp[r][c - 1] == SPACE || mazeTemp[r][c - 1] == TARGET)) {
			addNeighborASTAR(r, c - 1, pcurrent);

		}
		// right
		if (aStar_is_running && (mazeTemp[r][c + 1] == SPACE || mazeTemp[r][c + 1] == TARGET)) {
			addNeighborASTAR(r, c + 1, pcurrent);

		}


	}

}


