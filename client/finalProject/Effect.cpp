#include "stdafx.h"
#include "Effect.h"

Effect::Effect(Point p)
{
	point = p;
	frameX = 0;
}
Effect::~Effect()
{
}

void Effect::update()
{
	frameX += 10*TIMEMANAGER->getElapsedTime();
}

void Effect::render()
{
	int x = frameX;
	IMAGEMANAGER->findImage("explosion")->frameRender(getMemDC(), point.x, point.y, x, 0);
}
