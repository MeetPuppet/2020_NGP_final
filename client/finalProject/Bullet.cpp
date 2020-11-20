#include "stdafx.h"
#include "Bullet.h"

#define WIDTH 16
#define HEIGHT 24
#define SPEED 50

Bullet::Bullet()
{
	img = NULL;

	rc = { 0,0,0,0 };
	point = Point(0.f, 0.f);
}

Bullet::~Bullet()
{

}

HRESULT Bullet::init(image* IMG, Point p)
{
	img = IMG;
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
	img->render(getMemDC(), rc.left, rc.top);
}
