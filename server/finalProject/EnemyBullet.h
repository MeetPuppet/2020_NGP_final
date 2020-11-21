#pragma once
#include "gameNode.h"
class EnemyBullet :
	public gameNode
{
private:
	Point point;
	RECT rc;
public:
	EnemyBullet();
	~EnemyBullet();
	HRESULT init(Point p);
	void update();
	void render();
	RECT getRect() { return rc; }
};

