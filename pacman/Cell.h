#pragma once
class Cell
{
private:
	int row;
	int col;
	int F;
	int g;
	Cell* parent;
public:
	Cell();
	Cell(int r, int c,int f);
	Cell(int r, int c, Cell* p, int f);
	Cell(int r, int c, Cell * p,int f,int steps);
	Cell(int r, int c);
	~Cell();
	int getRow() { return row; }
	int getCol() { return col; }
	int getF() { return F;}
	int getG() { return g; }

	//void setTp(){}
	Cell* getParent() { return parent; }
};

