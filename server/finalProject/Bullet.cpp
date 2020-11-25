#include "stdafx.h"
#include "Bullet.h"

#define WIDTH 16
#define HEIGHT 24
#define SPEED 150

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

HRESULT Bullet::init(Point p)
{
	point = p;
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);

	return S_OK;
}

void Bullet::update()
{
	point.y -= SPEED * TIMEMANAGER->getElapsedTime();
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);
}

void Bullet::render()
{
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
}
