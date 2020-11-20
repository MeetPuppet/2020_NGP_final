#pragma once
#include "gameNode.h"

class Drone : public gameNode
{
private:
	image* img;

	RECT rc;
	Point point;
	int id;
public:
	Drone();
	~Drone();

	HRESULT init(image* IMG, Point p);
	void setPlayerDroneID(int no) { id = no; }
	int getPlayerDroneID() { return id; }

	void update();
	void render();
};

