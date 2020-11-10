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
	IMAGEMANAGER->addImage("black",1200, 800);
	IMAGEMANAGER->addImage("title", "image/title.bmp", 1200, 800, false, RGB(1,1,1));
	IMAGEMANAGER->addImage("cursor", "image/cursor.bmp", 39, 36, false,  RGB(1,1,1));
	
	mode = 0;
	point[0] = { 365,505 };
	point[1] = { 365,577 };

	alpha = 0;
	choose = false;
	return S_OK;
}
void title::release()
{
}
void title::update()
{
	float time = TIMEMANAGER->getElapsedTime();
	if (time < 0) time = 0.016;

	if (choose) {
		if(alpha < 250)
			alpha += 150* time;
		else {
			if(mode == 0)
				SCENEMANAGER->changeScene("P1world1");
			else
				SCENEMANAGER->changeScene("P2world1");
		}
	}
	else {
		if (KEYMANAGER->isOnceKeyUp(VK_UP)) {
			if (mode == 0)
				mode = 1;
			else
				mode = 0;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_DOWN)) {
			if (mode == 1)
				mode = 0;
			else
				mode = 1;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
			choose = true;
		}
	}
}
void title::render()
{
	IMAGEMANAGER->findImage("title")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("cursor")->render(getMemDC(), point[mode].x, point[mode].y);
	
	IMAGEMANAGER->findImage("black")->alphaRender(getMemDC(), alpha);
}