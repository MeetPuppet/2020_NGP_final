#include "stdafx.h"
#include "ending.h"
#include "playerNode.h"
#include "enemyNode.h"

ending::ending()
{
}

ending::~ending()
{
	delete playernode;
	delete enemynode;
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
}

void ending::render()
{
	if (playernode->getHP() == 0)
	{
		IMAGEMANAGER->findImage("defeat")->render(getMemDC(), 0, 0);
	}
	else if (enemynode->getHP() == 0)
	{
		IMAGEMANAGER->findImage("victory")->render(getMemDC(), 0, 0);
	}
}
