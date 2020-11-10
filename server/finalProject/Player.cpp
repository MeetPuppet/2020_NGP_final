#include "Player.h"

#define WIDTH 75
#define HEIGHT 80

Player::Player()
{
}

Player::~Player()
{
}

HRESULT Player::init()
{
	img = IMAGEMANAGER->addImage("galaga","image/player.bmp", WIDTH, HEIGHT, true, RGB(255,0,255));

	p = Point(WINSIZEX/2, WINSIZEY/2);

	rc = RectMakeCenter(p.x, p.y, WIDTH, HEIGHT);

	state = PS_IDLE;

	return S_OK;
}

void Player::KeySet()
{
	switch (state)
	{
	case PS_IDLE:
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
			state = PS_LEFT;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
			state = PS_RIGHT;
		}
		break;
	case PS_LEFT:
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT)) {
			state = PS_IDLE;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
			state = PS_RIGHT;
		}
		break;
	case PS_RIGHT:
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
			state = PS_LEFT;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT)) {
			state = PS_IDLE;
		}
		break;
	default:
		break;
	}

}
void Player::update()
{
	KeySet();
	switch (state)
	{
	case PS_LEFT:
		p.x -= 200 * TIMEMANAGER->getElapsedTime();
		break;
	case PS_RIGHT:
		p.x += 200 * TIMEMANAGER->getElapsedTime();
		break;
	}

	rc = RectMakeCenter(p.x, p.y, WIDTH, HEIGHT);
}

void Player::render()
{
	img->render(getMemDC(),rc.left, rc.top);
}
