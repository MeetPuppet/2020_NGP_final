#include "stdafx.h"
#include "EnemyBullet.h"

#define WIDTH 10
#define HEIGHT 10
#define SPEED 50

EnemyBullet::EnemyBullet()
{
}

EnemyBullet::~EnemyBullet()
{
}

HRESULT EnemyBullet::init(Point p)
{
	point = p;
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);

	return S_OK;
}

void EnemyBullet::update()
{
	point.y += SPEED * TIMEMANAGER->getElapsedTime();
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);
}

void EnemyBullet::render()
{
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
}
