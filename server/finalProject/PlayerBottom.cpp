#include "stdafx.h"
#include "PlayerBottom.h"

HRESULT PlayerBottom::init()
{
	point = Point(WINSIZEX / 2, WINSIZEY / 2 + 350);
	img = IMAGEMANAGER->addImage("galaga", "res/player.bmp",0,0, 75, 80, true, RGB(255, 0, 255));
	playerNode::init(img, point);

	return S_OK;
}
