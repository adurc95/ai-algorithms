#include "pacMan.h"
#include "eatingCoins.h"
#include "GLUT.H"
#include <math.h>




pacMan::pacMan()
{

}

pacMan::pacMan(int xc,int yc,int maze[][MSZ])
{
	mazeTemp[yc][xc] = START;
	maze[yc][xc] = START;
	
	isMoving = false;
	isScard = false;
	isDroppingWood = false;
	x = xc;
	y = yc;
	dy = y;
	dx = x;
	currentState = new eatingCoins();
	//currentState->OnStateEnter(this);


}

pacMan::~pacMan()
{
}


bool pacMan::Execute(int maze[][MSZ])
{
	maze[y][x] = SPACE;
	y = dy;
	x = dx;
	maze[y][x] = START;
	while (!open.empty()) {        //check whether pq empty or not
		open.pop();                 //erasing content one by one
		//cout << m.maths << ' ' << m.english << endl;
	}

	while (!targetLS.empty()) {        //check whether pq empty or not
		targetLS.pop();                 //erasing content one by one
		//cout << m.maths << ' ' << m.english << endl;
	}
	aStar_is_running = true;
	for (int t = 0; t < MSZ; t++)
	{
		for (int k = 0; k < MSZ; k++)
		{
			mazeTemp[t][k] = maze[t][k];
			if (mazeTemp[t][k] == coin) {
				targetLS.push(new Cell(t, k, abs(y - t) + abs(x - k)));

			}
			if (mazeTemp[t][k] == ghost) {
				fretLS.push(new Cell(t, k, abs(y - t) + abs(x - k)));

			}
		}
	}
	if (targetLS.empty()) {
		std::cout << "pacman wins!!!!!!!!!!!!!!!!!!!!!\n";
		return true;

	}

	if (isScard) {
		Cell* bastTarget = fretLS.top();
		Cell* pc = new Cell(y, x, abs(y - bastTarget->getRow()) + abs(x - bastTarget->getCol()));
		open.push(pc);
		grays.push_back(new Cell(y, x));
		for (int i = 0; i < 6; i++) {
			BfsIteration();
			if (!bfs_is_running)
				break;
		}
		currentState->OnStateEnter(this);




		
	}
	else {
		Cell* bastTarget = targetLS.top();
		Cell* pc = new Cell(y, x, abs(y - bastTarget->getRow()) + abs(x - bastTarget->getCol()));
		open.push(pc);
		grays.push_back(new Cell(y, x));
		for (int i = 0; i < 6; i++) {
			BfsIteration();
			if (!bfs_is_running)
				break;
		}
		currentState->OnStateEnter(this);
	}
	bfs_is_running = true;
	//setDirection(targetx, targety);
	return false;

}

void pacMan::setDirection(int targetY, int targetX)
{//chenge to astar
	mazeTemp[targetY][targetX] = TARGET;
	while (aStar_is_running) 
		RunAStardest();
}
void pacMan::RestorePath(Cell* pc)
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

void pacMan::addNeighborASTAR(int row, int col, Cell* pcurrent)
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
	if (isScard&& pcurrent->getF()>12)
	{
		
		aStar_is_running = false;
		RestorePath(pcurrent);
		
	}


	else if (mazeTemp[row][col] == WALL || mazeTemp[row][col] == BLACK) {
		return;
	}
	else // this is white neighbor
	{
		Cell* bastTarget = targetLS.top();

		int h = abs(col - bastTarget->getRow()) + abs(row - bastTarget->getCol());
		int f = h;

		pneighbor = new Cell(row, col, pcurrent, f, pcurrent->getG());
		mazeTemp[row][col] = GRAYP;

		open.push(pneighbor);


	}

}
void pacMan::RunAStardest()
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
		if (mazeTemp[r + 1][c] == SPACE || mazeTemp[r + 1][c] == TARGET ) {
			addNeighborASTAR(r + 1, c, pcurrent);

		}

		// down
		if (aStar_is_running && (mazeTemp[r - 1][c] == SPACE || mazeTemp[r - 1][c] == TARGET )) {
			addNeighborASTAR(r - 1, c, pcurrent);


		}
		// left
		if (aStar_is_running && (mazeTemp[r][c - 1] == SPACE || mazeTemp[r][c - 1] == TARGET )) {
			addNeighborASTAR(r, c - 1, pcurrent);

		}
		// right
		if (aStar_is_running && (mazeTemp[r][c + 1] == SPACE || mazeTemp[r][c + 1] == TARGET )) {
			addNeighborASTAR(r, c + 1, pcurrent);

		}


	}

}

void pacMan::CheckNeighbor(int row, int col, Cell* pcurrent)
{
	Cell* pneighbor;
	// is maze[row][col] a TARGET
	if (mazeTemp[row][col] == ghost)
	{
		//std::cout << "the solution has been found\n";
		bfs_is_running = false;
		gy = row;
		gx = col;
		//		RestorePath(pcurrent);
	}
	else // this is white neighbor
	{
		pneighbor = new Cell(row, col); // and pcurrent as parent
		grays.push_back(pneighbor);
		mazeTemp[row][col] = GRAYP;
	}
}

void pacMan::BfsIteration()
{
	Cell* pcurrent;
	int r, c;

	if (grays.empty())
	{
		std::cout << "There is no solution\n";
		bfs_is_running = false;
		isScard = true;
		return;
	}
	else // grays is not empty
	{
		pcurrent = *grays.begin();
		// remove pcurrent from grays and paint it black
		grays.erase(grays.begin());
		r = pcurrent->getRow();
		c = pcurrent->getCol();
		mazeTemp[r][c] = BLACK;
		// add non-visited neighbors
		// up
		if (mazeTemp[r + 1][c] == SPACE || mazeTemp[r + 1][c] == ghost)
			CheckNeighbor(r + 1, c, pcurrent);
		// down
		if (bfs_is_running && (mazeTemp[r - 1][c] == SPACE || mazeTemp[r - 1][c] == ghost))
			CheckNeighbor(r - 1, c, pcurrent);
		// left
		if (bfs_is_running && (mazeTemp[r][c - 1] == SPACE || mazeTemp[r][c - 1] == ghost))
			CheckNeighbor(r, c - 1, pcurrent);
		// right
		if (bfs_is_running && (mazeTemp[r][c + 1] == SPACE || mazeTemp[r][c + 1] == ghost))
			CheckNeighbor(r, c + 1, pcurrent);
	}

}

