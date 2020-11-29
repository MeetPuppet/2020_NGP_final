#pragma once
#include "gameNode.h"
class Effect :
	public gameNode
{
private:
	Point point;
	float frameX;
public:
	Effect(Point p);
	~Effect();

	void update();
	void render();

	float getFrameX() { return frameX; }
};

