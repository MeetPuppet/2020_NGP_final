#include "stdafx.h"
#include "Bullet.h"

#define WIDTH 16
#define HEIGHT 24
#define SPEED 150

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

void Bullet::enemy_update()
{
	point.y += SPEED * TIMEMANAGER->getElapsedTime();
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);
}

void Bullet::render()
{
	img->render(getMemDC(), rc.left, rc.top);
	if (KEYMANAGER->isToggleKey(VK_F3)) {
		Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
		char str[255];
		int x = point.x;
		wsprintf(str, "%d", id);
		TextOut(getMemDC(), point.x, point.y, str, strlen(str));
	}
}
