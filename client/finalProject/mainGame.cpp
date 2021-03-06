#include "stdafx.h"
#include "mainGame.h"
#include "title.h"
#include "inGame.h"
#include "ending.h"

mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

HRESULT mainGame::init()			//초기화 함수
{
	gameNode::init(true);

	SCENEMANAGER->addScene("title", new title);
	SCENEMANAGER->addScene("inGame", new inGame);
	SCENEMANAGER->addScene("ending_lose", new ending(false));
	SCENEMANAGER->addScene("ending_win", new ending(true));
	SCENEMANAGER->changeScene("title");

	return S_OK;
}

void mainGame::release()			//메모리 해제 함수
{
	gameNode::release();
	//delete p;//할당 해제
	//delete q;	
}

void mainGame::update()				//연산 함수
{
	gameNode::update();	
	SCENEMANAGER->update();
}

void mainGame::render()		//그려주는 함수(a.k.a WM_PAINT)
{
	//흰색 도화지 한장~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== 건들지마라 ======================

	SCENEMANAGER->render();

	//==================== 건들지마라 =======================

	if (KEYMANAGER->isToggleKey(VK_F3)) 
		TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}

