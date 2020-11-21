#include "stdafx.h"
#include "PlayerTop.h"

#define WIDTH 75  //�̹��� ���α���
#define HEIGHT 80 //�̹��� ���α���

HRESULT PlayerTop::init()
{
	playerNode::init(
		IMAGEMANAGER->addImage("Redgalaga", "res/enemy_player.bmp", 75, 80, true, RGB(255, 0, 255)),
		Point(WINSIZEX / 2, WINSIZEY / 2 - 200)
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
		point.x += MOVE_SPEED * TIMEMANAGER->getElapsedTime();
		break;
	case PS_RIGHT:
		point.x -= MOVE_SPEED * TIMEMANAGER->getElapsedTime();
		break;
	}
}