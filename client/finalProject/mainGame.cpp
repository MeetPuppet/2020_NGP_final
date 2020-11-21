#include "stdafx.h"
#include "mainGame.h"
#include "playerNode.h"
#include "enemyNode.h"
#include "Bullet.h"
#include "Drone.h"


mainGame::mainGame()
{
}

mainGame::~mainGame()
{
	delete playernode;
	delete enemynode;
}

HRESULT mainGame::init()			//초기화 함수
{
	gameNode::init(true);
	playernode = new playerNode();
	playernode->init(IMAGEMANAGER->addImage("player", "res/player.bmp", 75, 80, true, RGB(255, 0, 255)), Point(WINSIZEX / 2, WINSIZEY / 2 + 200));
	CLIENT->setPlayerRef(playernode);

	enemynode = new enemyNode();
	enemynode->init(IMAGEMANAGER->addImage("enemy", "res/enemy_player.bmp", 75, 80, true, RGB(255, 0, 255)), Point(WINSIZEX / 2, WINSIZEY / 2 - 200));
	CLIENT->setEnemyRef(enemynode);

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
	playernode->update();
	enemynode->update();
}

void mainGame::render()		//그려주는 함수(a.k.a WM_PAINT)
{
	//흰색 도화지 한장~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== 건들지마라 ======================

	playernode->render();
	enemynode->render();

	
	char buf[20] = { NULL };
	wsprintf(buf, "%d", CLIENT->getCheckCount());
	TextOut(getMemDC(), 600, 10, buf, strlen(buf));

	//==================== 건들지마라 =======================

	if (KEYMANAGER->isToggleKey(VK_F3)) 
		TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
