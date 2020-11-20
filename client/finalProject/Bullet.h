#pragma once
#include "gameNode.h"

class Bullet :
	public gameNode
{
private:
	image* img;

	RECT rc;
	Point point;

public:
	Bullet();
	~Bullet();

	HRESULT init(image* IMG, Point p);

	void update();
	void render();
};

