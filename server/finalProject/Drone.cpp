#include "stdafx.h"
#include "Drone.h"

#define WIDTH 55
#define HEIGHT 60
#define SPEED 50

Drone::Drone()
{
}

Drone::~Drone()
{
}

HRESULT Drone::init(Point p)
{
	point = p;
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);
	return S_OK;
}

void Drone::update()
{
	point.y -= SPEED * TIMEMANAGER->getElapsedTime();
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);
}

void Drone::render()
{
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
}
