#include "GLUT.h"

#include <time.h>
#include <vector>
#include "Cell.h"
#include <iostream>
#include <algorithm>    // std::sort
#include <cstdlib>
#include <queue>
#include "CompareCells.h"




using namespace std;


const int MSZ = 100; // maze size
const int WALL = 0;
const int SPACE = 1;
const int START = 2;
const int TARGET = 3;
const int GRAY = 4;
const int BLACK = 5;
const int PATH = 6;


int maze[MSZ][MSZ] = {0};
bool bfs_is_running = false;
bool aStar_is_running = false;

// defines queue of Cells
//vector<Cell*> open;
vector<Cell*> closed;
vector<Cell*> successor;
int targetx;
int targety;

priority_queue <Cell*, vector<Cell*>, CompareCells> open;
//vector<Cell*> solution;
//bool solutionIsReady = false;
void InitMaze();

void init()
{
	srand(time(0)); // seed random numbers
	glClearColor(0, 0, 0.2, 0); // RGB - sets background color
	glOrtho(0, MSZ, 0, MSZ, -1, 1); // setup coordinate system
	InitMaze();
}

void InitMaze()
{
	int i, j;

	// the border is WALL by default 

	for(i=1;i<MSZ-1;i++)
		for (j = 1; j < MSZ - 1; j++)
		{
			if (i % 2 == 1) // more SPACES
			{
				if (rand() % 100 < 85)
					maze[i][j] = SPACE;
				else
					maze[i][j] = WALL;
			}
			else // i is even: more walls
			{
				if (rand() % 100 < 70)
					maze[i][j] = WALL;
				else
					maze[i][j] = SPACE;
			}
		}
	maze[MSZ / 2][MSZ / 2] = START;
	// add Start Point to grays
	targetx = rand() % MSZ;
	targety = rand() % MSZ;
	Cell* pc = new Cell(MSZ / 2, MSZ / 2, abs(MSZ / 2 - targety) + abs(MSZ / 2 - targetx));
	open.push(pc);
	//grays.push_back(tc);
	maze[targetx][targety] = TARGET;

}


void DrawMaze()
{
	int i, j;

	for(i=0;i<MSZ;i++)
		for (j = 0; j < MSZ; j++)
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
			}
			glBegin(GL_POLYGON);
			glVertex2d(j, i);
			glVertex2d(j, i+1);
			glVertex2d(j+1, i+1);
			glVertex2d(j+1, i);
			glEnd();
		}
}

void RestorePath(Cell* pc)
{
	while (pc != nullptr)
	{
		maze[pc->getRow()][pc->getCol()] = PATH;
		pc = pc->getParent();
	}
}

void addNeighbor(int row, int col, Cell* pcurrent)
{
	Cell* pneighbor;
	
	// is maze[row][col] a TARGET
	if ((maze[row][col] == TARGET))
	{
		cout << "the solution has been found\n";
		bfs_is_running = false;
		RestorePath(pcurrent);
	}
	else if (maze[row][col] == WALL|| maze[row][col]== BLACK) {
		return;
	}
	else // this is white neighbor
	{
		
		pneighbor = new Cell(row, col, pcurrent, abs(col - targety) + abs(row - targetx));
		maze[row][col] = GRAY;
		open.push(pneighbor);
		
	}
}

void greedyIteration()
{
	Cell* pcurrent;
	int r, c;

	if (open.empty())
	{
		cout << "There is no solution\n";
		bfs_is_running = false;
		return;
	}
	else // grays is not empty
	{
		pcurrent = open.top();

		open.pop();
		r = pcurrent->getRow();
		c = pcurrent->getCol();
		closed.push_back(pcurrent);
		
			maze[r][c] = BLACK;
	

		if (maze[r + 1][c] == SPACE || maze[r + 1][c] == TARGET || maze[r - 1][c])
			addNeighbor(r + 1, c, pcurrent);
		
		// down
		if (bfs_is_running && (maze[r - 1][c] == SPACE || maze[r - 1][c] == TARGET || maze[r - 1][c]))
			addNeighbor(r - 1, c, pcurrent);
			// left
		if (bfs_is_running && (maze[r ][c- 1] == SPACE || maze[r ][c- 1] == TARGET || maze[r][c - 1] ))
			addNeighbor(r, c - 1, pcurrent);
		// right
		if (bfs_is_running && (maze[r][c + 1] == SPACE || maze[r][c + 1] == TARGET || maze[r][c + 1] ))
			addNeighbor(r, c + 1, pcurrent);

	}

}
void addNeighborASTAR(int row, int col, Cell* pcurrent)
{
	Cell* pneighbor;
	// is maze[row][col] a TARGET
	if ((maze[row][col] == TARGET))
	{
		cout << "the solution has been found\n";
		aStar_is_running = false;
		RestorePath(pcurrent);
	}
	else if (maze[row][col] == WALL|| maze[row][col]== BLACK) {
		return;
	}
	else // this is white neighbor
	{

		int h = abs(col - targety) + abs(row - targetx);
		int f = h;
		
		pneighbor = new Cell(row, col, pcurrent, f, pcurrent->getG());
		maze[row][col] = GRAY;

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
		cout << "There is no solution\n";
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

		maze[r][c] = BLACK;
		if (maze[r + 1][c] == SPACE || maze[r + 1][c] == TARGET || maze[r - 1][c]) {
			addNeighborASTAR(r + 1, c, pcurrent);
		
		}

		// down
		if (aStar_is_running && (maze[r - 1][c] == SPACE || maze[r - 1][c] == TARGET || maze[r - 1][c])) {
			addNeighborASTAR(r - 1, c, pcurrent);


		}
		// left
		if (aStar_is_running && (maze[r][c - 1] == SPACE || maze[r][c - 1] == TARGET || maze[r][c - 1])) {
			addNeighborASTAR(r, c - 1, pcurrent);
	
		}
		// right
		if (aStar_is_running && (maze[r][c + 1] == SPACE || maze[r][c + 1] == TARGET || maze[r][c + 1])) {
			addNeighborASTAR(r, c + 1, pcurrent);
	
		}


	}

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // fills all the frame buffer with background color

	DrawMaze();
	glutSwapBuffers();// show what was drawn in "frame buffer"
}

void idle()
{
	if (bfs_is_running)
		greedyIteration();
	if (aStar_is_running)
		RunAStar();
	glutPostRedisplay(); // calls indirectly to display
}

void menu(int choice)
{
	switch (choice)
	{
	case 1: // bfs
		bfs_is_running = true;
		break;
	case 2: // bfs
		aStar_is_running = true;
		break;
	}
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
	glutAddMenuEntry("Run BestFS", 1);
	glutAddMenuEntry("Run AStar", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();

	glutMainLoop();
}