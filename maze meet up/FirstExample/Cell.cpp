#include "Cell.h"



Cell::Cell()
{
}

Cell::Cell(int r, int c, bool tf)
{
	row = r;
	col = c;
	targetPath = tf;

	parent = nullptr; // has no parent
}

Cell::Cell(int r, int c,Cell* p, bool tf)
{
	row = r;
	col = c;
	parent = p; 
	targetPath = tf;
}



Cell::~Cell()
{
}
