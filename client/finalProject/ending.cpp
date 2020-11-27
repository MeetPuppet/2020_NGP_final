#include "stdafx.h"
#include "ending.h"

ending::ending()
{
}

ending::~ending()
{
}

HRESULT ending::init()
{
	IMAGEMANAGER->addImage("fix", "res/fix_now.bmp", 800, 800, false, RGB(0, 0, 0));
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
	IMAGEMANAGER->findImage("fix")->render(getMemDC(), 0, 0);
}
