#include "stdafx.h"
#include "title.h"



title::title()
{
}


title::~title()
{
}

HRESULT title::init()
{
	IMAGEMANAGER->addImage("title", "res/tiltle.bmp",800, 800, false, RGB(0,0,0));

	return S_OK;
}
void title::release()
{
}
void title::update()
{
	if (KEYMANAGER->isOnceKeyDown('Z')) {
		SCENEMANAGER->changeScene("inGame");
	}
}
void title::render()
{
	IMAGEMANAGER->findImage("title")->render(getMemDC(), 0, 0);
}