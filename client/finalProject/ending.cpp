#include "stdafx.h"
#include "ending.h"

ending::ending(bool winner)
{
	isP1 = winner;
}

ending::~ending()
{
}

HRESULT ending::init()
{
	IMAGEMANAGER->addImage("defeat", "res/defeat.bmp", 800, 800, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("victory", "res/victory.bmp", 800, 800, false, RGB(0, 0, 0));

	return S_OK;
}

void ending::release()
{
}

void ending::update()
{
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		SCENEMANAGER->changeScene("title");
	}
}

void ending::render()
{
	if (!isP1)
	{
		IMAGEMANAGER->findImage("defeat")->render(getMemDC(), 0, 0);
	}
	else if (isP1)
	{
		IMAGEMANAGER->findImage("victory")->render(getMemDC(), 0, 0);
	}
}
