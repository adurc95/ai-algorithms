#pragma once
#include "Cell.h"
class CompareCells
{
public:
	CompareCells();
	~CompareCells();
	bool operator() (Cell* pn1, Cell* pn2) {
		return pn1->getF() > pn2->getF();
	}
};

