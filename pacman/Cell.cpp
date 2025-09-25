#include "Cell.h"



Cell::Cell()
{
}
Cell::Cell(int r, int c)
{
	row = r;
	col = c;
}
Cell::Cell(int r, int c, int f)
{
	row = r;
	col = c;
	F = f;
	parent = nullptr; // has no parent
}

Cell::Cell(int r, int c,Cell* p, int f)
{
	row = r;
	col = c;
	F = f;
	parent = p; 
	
}
Cell::Cell(int r, int c, Cell* p, int f, int steps)
{
	row = r;
	col = c;
	g = steps + 1;
	F = f + g;
	parent = p;

}



Cell::~Cell()
{
}
