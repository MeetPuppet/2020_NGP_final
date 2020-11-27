#include "stdafx.h"
#include "loading.h"

loading::loading()
{
}

loading::~loading()
{
}

HRESULT loading::init()
{
	IMAGEMANAGER->addImage("nothing", "res/nothing.bmp", 800, 800, false, RGB(0, 0, 0));
	return S_OK;
}

void loading::release()
{
}

void loading::update()
{
}

void loading::render()
{
	IMAGEMANAGER->findImage("nothing")->render(getMemDC(), 0, 0);
}
