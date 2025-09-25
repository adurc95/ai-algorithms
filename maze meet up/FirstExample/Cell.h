#pragma once
class Cell
{
private:
	int row;
	int col;
	bool targetPath;
	Cell* parent;
public:
	Cell();
	Cell(int r, int c,bool tf);
	Cell(int r, int c, Cell * p, bool tf);
	~Cell();
	int getRow() { return row; }
	int getCol() { return col; }
	bool getTp() { return targetPath;}
	//void setTp(){}
	Cell* getParent() { return parent; }
};

