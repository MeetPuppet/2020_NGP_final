#pragma once
#include "gameNode.h"
class Bullet :
	public gameNode
{
private:
	Point point;
	RECT rc;
public:
	Bullet();
	~Bullet();
	HRESULT init(Point p);
	void update();
	void render();
};

