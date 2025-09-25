#include "GLUT.h"

#include <time.h>
#include <vector>
#include "Cell.h"
#include <iostream>

using namespace std;


const int MSZ = 100; // maze size
const int WALL = 0;
const int SPACE = 1;
const int START = 2;
const int TARGET = 3;
const int GRAY = 4;
const int BLACK = 5;
const int PATH = 6;
const int TP = 7;
const int TPBLACK = 8;



int maze[MSZ][MSZ] = {0};
bool meet_up_is_running = false;
bool dfs_is_running = false;

// defines queue of Cells
vector<Cell*> grays;
vector<Cell*> Tpath;
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
	int targetx = rand() % MSZ;
	int targety = rand() % MSZ;
	Cell* pc = new Cell(MSZ / 2, MSZ / 2, false);
	Cell* tc = new Cell(targetx, targety,true);
	grays.push_back(pc);
	//grays.push_back(tc);
	Tpath.push_back(tc);
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
			case TP:
				glColor3d(255, 165, 0); // hopfully  orange 
				break;
			case TPBLACK:
				glColor3d(0, 165, 255); // hopfully   
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

void CheckNeighbor(int row, int col, Cell* pcurrent)
{
	Cell* pneighbor;
	
	//if (((maze[row][col] == TARGET || maze[row][col] == TPBLACK) && !pcurrent->getTp()))
		// is maze[row][col] a TARGET 
	if ( ((maze[row][col] == TARGET|| maze[row][col] == TPBLACK|| maze[row][col]==TP)&& !pcurrent->getTp())|| ((maze[row][col] == START||maze[row][col] == GRAY|| maze[row][col] == BLACK) && pcurrent->getTp()))
	{
		cout << "the solution has been found\n";
		meet_up_is_running = false;
		dfs_is_running = false;
		RestorePath(pcurrent);
	}
	
	else // this is white neighbor
	{
		//bool istpath=false;
		if (pcurrent->getTp()) {
			pneighbor = new Cell(row, col, pcurrent, true);
			maze[row][col] = TP;
			Tpath.push_back(pneighbor);
		}
		else{
			pneighbor = new Cell(row, col, pcurrent, false);
			maze[row][col] = GRAY;
			grays.push_back(pneighbor);
		}
		
		
		
		
	}
}

void bfs_meetup_iteration()
{
	Cell* pcurrent;
	int r, c;

	if (grays.empty())
	{
		cout << "There is no solution\n";
		meet_up_is_running = false;
		return;
	}
	else // grays is not empty
	{
		pcurrent = *grays.begin();

		// remove pcurrent from grays and paint it black
		grays.erase(grays.begin());
		r = pcurrent->getRow();
		c = pcurrent->getCol();

			maze[r][c] = BLACK;
	

		// add non-visited neighbors
		// up
		if (maze[r + 1][c] == SPACE || maze[r + 1][c] == TARGET || maze[r - 1][c] == TP)
			CheckNeighbor(r + 1, c, pcurrent);
		
		// down
		if (meet_up_is_running && (maze[r - 1][c] == SPACE || maze[r - 1][c] == TARGET || maze[r - 1][c] == TP))
			CheckNeighbor(r - 1, c, pcurrent);
			// left
		if (meet_up_is_running && (maze[r ][c- 1] == SPACE || maze[r ][c- 1] == TARGET || maze[r][c - 1] == TP))
			CheckNeighbor(r, c - 1, pcurrent);
		// right
		if (meet_up_is_running && (maze[r][c + 1] == SPACE || maze[r][c + 1] == TARGET || maze[r][c + 1] == TP))
			CheckNeighbor(r, c + 1, pcurrent);


		pcurrent = *Tpath.begin();
		//cout << pcurrent;
		Tpath.erase(Tpath.begin());
		r = pcurrent->getRow();
		c = pcurrent->getCol();
		maze[r][c] = TPBLACK;

		if (maze[r + 1][c] == SPACE ||  maze[r - 1][c] == TP)
			CheckNeighbor(r + 1, c, pcurrent);

		// down
		if (meet_up_is_running && (maze[r - 1][c] == SPACE || maze[r - 1][c] == TP))
			CheckNeighbor(r - 1, c, pcurrent);
		// left
		if (meet_up_is_running && (maze[r][c - 1] == SPACE  || maze[r][c - 1] == TP))
			CheckNeighbor(r, c - 1, pcurrent);
		// right
		if (meet_up_is_running && (maze[r][c + 1] == SPACE  || maze[r][c + 1] == TP))
			CheckNeighbor(r, c + 1, pcurrent);

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
	if (meet_up_is_running)
		bfs_meetup_iteration();


	glutPostRedisplay(); // calls indirectly to display
}

void menu(int choice)
{
	switch (choice)
	{
	case 1: // bfs
		meet_up_is_running = true;
		break;
	
	}
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // double means it uses double buffer
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(600, 100);
	glutCreateWindow("meat up");

	glutDisplayFunc(display); // refresh function
	glutIdleFunc(idle); // runs all the time in the background
// add menu
	glutCreateMenu(menu);
	glutAddMenuEntry("Run meat up", 1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();

	glutMainLoop();
}