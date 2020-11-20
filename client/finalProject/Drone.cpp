#include "stdafx.h"
#include "Drone.h"

#define WIDTH 55
#define HEIGHT 60
#define SPEED 50

Drone::Drone()
{
	img = NULL;

	rc = { 0,0,0,0 };
	point = Point(0.f, 0.f);
}

Drone::~Drone()
{

}

HRESULT Drone::init(image* IMG, Point p)
{
	img = IMG;
	point = p;
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);

	return S_OK;
}

void Drone::update()
{
	point.y -= SPEED * TIMEMANAGER->getElapsedTime();
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);
}

void Drone::enemy_update()
{
	point.y += SPEED * TIMEMANAGER->getElapsedTime();
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);
}

void Drone::render()
{
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	img->render(getMemDC(), rc.left, rc.top);
}