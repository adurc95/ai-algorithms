#pragma once
class Rooms
{
private:
	int starX;
	int starY;
	int hight;
	int wight;
	int centerx;
	int centery;
public:
	Rooms();
	Rooms(int starX, int starY, int hight, int wight);
	~Rooms();
	int getstarX() { return starX; }
	int getstarY() { return starY; }
	int gethight() { return hight; }
	int getWight() { return wight; }
	int getCenterx() { return centerx;}
	int getCentery() { return centery; }
};

