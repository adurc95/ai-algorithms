#include "GLUT.h"

#include <time.h>
#include <vector>
#include "Cell.h"
#include <iostream>
#include <algorithm>    // std::sort
#include <cstdlib>
#include <queue>
#include<tuple> 
#include "CompareCells.h"
#include "rooms.h"
#include "pacMan.h"
#include "scaryGhost.h"
//scaryGhost



using namespace std;

bool on = true;
const int MSZMain = 100; // maze size
const int WALL = 0;
const int SPACE = 1;
const int START = 2;
const int TARGET = 3;
const int GRAY = 4;
const int BLACK = 5;
const int PATH = 6;
const int coin = 7;
const int ghost = 8;

pacMan* p;
scaryGhost* g1;

scaryGhost* g2;
scaryGhost* g3;

int maze[MSZMain][MSZMain] = {0};
int maze2[MSZMain][MSZMain] = { 0 };

bool bfs_is_running = false;
bool aStar_is_running = false;

// defines queue of Cells
//vector<Cell*> open;
vector<Cell*> closed;
//vector<Cell*> successor;
vector<Rooms*> rooms;


//vector<tuple<int,int, int,int, int> > rooms;
int targetx;
int targety;

priority_queue <Cell*, vector<Cell*>, CompareCells> open;
//vector<Cell*> solution;
//bool solutionIsReady = false;
void InitMaze();
bool makeRoom(int c, int r);
void drillePaths();
void drille(Rooms* current, Rooms* dest);
void init()
{
	srand(time(0)); // seed random numbers
	glClearColor(0, 0, 0.2, 0); // RGB - sets background color
	glOrtho(0, MSZMain, 0, MSZMain, -1, 1); // setup coordinate system
	InitMaze();
}

void InitMaze()
{
	int i, j;

	int qurtetx = 40;
	int qurtety = 40;
	int bordx = 25;
	int bordy = 25;
	// the border is WALL by default 
	for (i = 0; i < 6; i++) {

		bool on = makeRoom(bordx + (rand() % qurtetx), bordy + (rand()  % qurtety));
		while (!on)
		{
			on = makeRoom(bordx + (rand() % qurtetx), bordy + (rand()  % qurtety));

		}
		
	}
	drillePaths();



}
void drillePaths() {
	vector<Rooms*> concted;
	vector<Rooms*> not;
	Rooms* current;
	not.insert(not.end(), rooms.begin(), rooms.end());
	int distensc = 0;
	int xpac, ypac, xghost, yghost;
	xghost = rooms.front()-> getCenterx();
	yghost = rooms.front()->getCentery();
	for (int i = 0; i < rooms.size();i++) {
		
		current = not.back();
		not.pop_back();
		for each (auto dest in not) {
			drille(current, dest);
			int newdist = sqrt(pow(dest->getCenterx() - current->getCenterx(), 2) + pow(dest->getCentery() - current->getCentery(), 2));
			if (distensc < newdist) {
				distensc = newdist;
				xpac = current->getCenterx();
				ypac = current->getCentery();
				
			}

		}
		not.insert(not.begin(), current);
		//break;
	}
	p = new pacMan(xpac, ypac,maze);
	//	scaryGhost(int x, int y, int maze[][MSZG], pacMan* pacMan);

	g1 = new scaryGhost(xghost + 1, yghost + 1, maze, p);
	g2 = new scaryGhost(xghost - 1, yghost - 1, maze, p);
	g3 = new scaryGhost(xghost , yghost , maze, p);

}
void RunAStar();
void drille(Rooms* current, Rooms* dest) {
	int targetx =dest->getCenterx();
	int targety = dest->getCentery();
	
	int x = current->getCenterx();
	int y = current->getCentery();
	Cell* pc= new Cell(y,x, abs(y - targety) + abs(y - targetx));
	open.push(pc);

	//std::copy(&maze[0][0], &maze[0][0] + 50 * 50, &maze2[0][0]);
	for (int x = 0; x < MSZMain; x++)
	{
		for (int y = 0; y < MSZMain; y++)
		{
			maze2[x][y] = maze[x][y];
		}
	}
	maze2[targety][targetx] = TARGET;
	aStar_is_running = true;
	while(aStar_is_running) {
		RunAStar();
	}
	//maze[targety][targetx] = SPACE;
	while (!open.empty())
		open.pop();
}

void RestorePath(Cell* pc)
{

	while (pc != nullptr)
	{
		maze[pc->getRow()][pc->getCol()] = SPACE;
		pc = pc->getParent();
	}
}
void addNeighborASTAR(int row, int col, Cell* pcurrent)
{
	Cell* pneighbor;
	// is maze[row][col] a TARGET
	if ((maze2[row][col] == TARGET))
	{
		//cout << "the solution has been found\n";
		aStar_is_running = false;
		RestorePath(pcurrent);

	}
	else if (maze2[row][col] == BLACK) {
		return;
	}
	else // this is white neighbor or path
	{

		int h = abs(col - targety) + abs(row - targetx);
		
		int f = h;
		
		if (maze2[row][col] == WALL)
			pneighbor = new Cell(row, col, pcurrent, f, pcurrent->getG()+3);
		else {
			pneighbor = new Cell(row, col, pcurrent, f, pcurrent->getG());

		}

		maze2[row][col] = GRAY;

		open.push(pneighbor);


	}
}
void RunAStar()
{
	Cell* pcurrent;
	int r, c;
	//int successorNum = 0;
	if (open.empty())
	{
		//cout << "There is no solution\n";
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
		//if(maze[r][c]!=PATH)
		maze2[r][c] = BLACK;
		if (r>0&&r < 100) {
			if (maze2[r + 1][c] == SPACE || maze2[r + 1][c] == TARGET || maze2[r + 1][c] == WALL) {
				addNeighborASTAR(r + 1, c, pcurrent);

			}

			// down
			if (aStar_is_running && (maze2[r - 1][c] == SPACE || maze2[r - 1][c] == TARGET || maze2[r - 1][c] == WALL)) {
				addNeighborASTAR(r - 1, c, pcurrent);


			}
		}
		if (c>0&&c < 100) {
			// left
			if (aStar_is_running && (maze2[r][c - 1] == SPACE || maze2[r][c - 1] == TARGET || maze2[r][c - 1] == WALL)) {
				addNeighborASTAR(r, c - 1, pcurrent);

			}
			// right
			if (aStar_is_running && (maze2[r][c + 1] == SPACE || maze2[r][c + 1] == TARGET || maze2[r][c + 1] == WALL)) {
				addNeighborASTAR(r, c + 1, pcurrent);

			}
		}
		


	}

}

bool makeRoom(int c, int r) {
	int hight = 10 + rand() % 10;
	int wight = 10 + rand() % 10;


	for (int k = c-3; k < hight + c+3; k++)
		for (int t = r-3; t < wight + r+3; t++) {
			if (maze[k][t] == SPACE)
			{
				return false;
			

			}

		}
	
	if (c + hight == 100 || r + wight == 100 || r == 0 || c == 0)
		return false;
	//	if (maze[(c + hight)][r + wight] == WALL&& maze[(c + hight+1)][r + wight+1] == WALL && maze[(c + hight+1)][r + wight] == WALL && maze[(c + hight)][r + wight+1] == WALL && maze[c][r] == WALL && maze[c + hight][r] == WALL && maze[c][r + wight] == WALL && maze[c+ (hight/2)][r + (wight/2)] == WALL && maze[c + (hight / 2)][1+r + (wight / 2)] == WALL && maze[1+c + (hight / 2)][r + (wight / 2)] == WALL && maze[1 + c + (hight / 2)][1+r + (wight / 2)] == WALL && maze[c-1][r] == WALL && maze[c][r-1] == WALL && maze[c - 1][r-1] == WALL) {

	if ( maze[(c + hight+1)][r + wight+1] == WALL && maze[(c + hight+1)][r + wight] == WALL && maze[(c + hight)][r + wight+1] == WALL && maze[c-1][r-1] == WALL && maze[c + hight+1][r] == WALL && maze[c][r + wight+1] == WALL  &&  maze[c-1][r] == WALL && maze[c][r-1] == WALL && maze[c - 1][r-1] == WALL) {
		for (int k= c; k < hight+ c; k++)
			for (int t = r; t < wight+r; t++) {
				int ran = rand() % 10+3;
				if(t% ran ==0&&k%ran==0)
					maze[k][t] = coin;
				else {
					maze[k][t] = SPACE;

				}

				
			}
		Rooms* temp = new Rooms(r, c, hight, wight);
		rooms.push_back(temp);
		return true;
	}
	else {
		 //makeRoom(1 + rand() % (MSZMain - 2), 1 + rand() % (MSZMain - 2));
		 return false;
	}
	
}

void DrawMaze()
{
	int i, j;

	for(i=0;i<MSZMain;i++)
		for (j = 0; j < MSZMain; j++)
		{
			// set color
			switch (maze[i][j])
			{
			case WALL:
				glColor3d(0.3, 0, 0);// dark red
				break;
			case SPACE:
				glColor3d(1, 1, 1); // white
				break;
			case START:
				glColor3d(0.5, 0.7, 1);// light blue
				break;
			case TARGET:
				glColor3d(1, 0, 0); // red
				break;
			case GRAY:
				glColor3d(0, 0.5, 0); // dark green
				break;
			case BLACK:
				glColor3d(0.7, 1, 0.7); // light green
				break;
			case PATH:
				glColor3d(0.7, 0, 0.7); // magenta
				break;
			case coin:
				glColor3d(255, 255, 0); // magenta
				break;
			case ghost:
				glColor3d(0, 0, 0); // 
				break;
			}
			

			glBegin(GL_POLYGON);
			glVertex2d(j, i);
			glVertex2d(j, i+1);
			glVertex2d(j+1, i+1);
			glVertex2d(j+1, i);
			glEnd();
		}
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // fills all the frame buffer with background color
	DrawMaze();
	//maze[p->gety()][p->getx()] = TARGET;
	//p->DrawMe();
	glutSwapBuffers();// show what was drawn in "frame buffer"
	
	

}

void idle()
{
	/*if (bfs_is_running)
		greedyIteration();
	if (aStar_is_running)
		RunAStar();*/
		//maze[p->gety()][p->getx()] = SPACE;
	if (on) {
		if (p->Execute(maze))
			on = false;

		if (g1->Execute(maze)|| g2->Execute(maze)|| g3->Execute(maze)) {
			on = false;
		}
			
	}
	
	//maze[p->gety()][p->getx()] = SPACE;
	glutPostRedisplay(); // calls indirectly to display
}

void menu(int choice)
{


}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // double means it uses double buffer
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(600, 100);
	glutCreateWindow("BestFS/AStar");

	glutDisplayFunc(display); // refresh function
	glutIdleFunc(idle); // runs all the time in the background
// add menu
	glutCreateMenu(menu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();

	glutMainLoop();
}