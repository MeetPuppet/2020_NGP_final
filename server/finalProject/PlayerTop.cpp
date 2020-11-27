#include "stdafx.h"
#include "PlayerTop.h"

#define WIDTH 75  //이미지 가로길이
#define HEIGHT 80 //이미지 세로길이

HRESULT PlayerTop::init()
{
	playerNode::init(
		IMAGEMANAGER->addImage("Redgalaga", "res/enemy_player.bmp", 75, 80, true, RGB(255, 0, 255)),
		Point(WINSIZEX / 2, WINSIZEY / 2 - 350)
	);

	return S_OK;
}

void PlayerTop::update()
{
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);
	StateMove();
}

void PlayerTop::StateMove()
{
	switch (state)
	{
	case PS_IDLE:
		break;
	case PS_LEFT:
		if (rc.right < WINSIZEX) {
			point.x += MOVE_SPEED * TIMEMANAGER->getElapsedTime();
		}
		else {
			point.x -= (rc.right - WINSIZEX);
		}

		break;
	case PS_RIGHT:
		if (rc.left > 0) {
			point.x -= MOVE_SPEED * TIMEMANAGER->getElapsedTime();
		}
		else {
			point.x -= rc.left;
		}
		break;
	}
}