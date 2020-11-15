#include "stdafx.h"
#include "PlayerTop.h"

HRESULT PlayerTop::init()
{
	playerNode::init(
		IMAGEMANAGER->addImage("Redgalaga", "res/enemy_player.bmp", 75, 80, true, RGB(255, 0, 255)),
		Point(WINSIZEX / 2, WINSIZEY / 2 - 200)
	);

	return S_OK;
}
