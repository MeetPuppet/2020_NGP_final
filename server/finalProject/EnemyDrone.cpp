#include "stdafx.h"
#include "EnemyDrone.h"

#define WIDTH 55
#define HEIGHT 60
#define SPEED 50

EnemyDrone::EnemyDrone()
{
}
EnemyDrone::~EnemyDrone()
{
}

HRESULT EnemyDrone::init(Point p)
{
	point = p;
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);
	return S_OK;
}

void EnemyDrone::update()
{
	point.y += SPEED * TIMEMANAGER->getElapsedTime();
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);
}

void EnemyDrone::render()
{
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
}
