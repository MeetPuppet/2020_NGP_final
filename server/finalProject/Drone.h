#pragma once
#include "gameNode.h"
class Drone :
	public gameNode
{
private:
	Point point;
	RECT rc;
public:
	Drone();
	~Drone();
	HRESULT init(Point p);
	void update();
	void render();
	RECT getRect() { return rc; }
};

