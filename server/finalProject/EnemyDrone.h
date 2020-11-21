#pragma once
#include "gameNode.h"
class EnemyDrone :
	public gameNode
{
private:
	Point point;
	RECT rc;
public:
	EnemyDrone();
	~EnemyDrone();
	HRESULT init(Point p);
	void update();
	void render();
	RECT getRect() { return rc; }
};

