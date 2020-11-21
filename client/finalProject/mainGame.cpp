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

HRESULT mainGame::init()			//�ʱ�ȭ �Լ�
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

void mainGame::release()			//�޸� ���� �Լ�
{
	gameNode::release();
	//delete p;//�Ҵ� ����
	//delete q;	
}

void mainGame::update()				//���� �Լ�
{
	gameNode::update();	
	playernode->update();
	enemynode->update();
}

void mainGame::render()		//�׷��ִ� �Լ�(a.k.a WM_PAINT)
{
	//��� ��ȭ�� ����~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== �ǵ������� ======================

	playernode->render();
	enemynode->render();

	
	char buf[20] = { NULL };
	wsprintf(buf, "%d", CLIENT->getCheckCount());
	TextOut(getMemDC(), 600, 10, buf, strlen(buf));

	//==================== �ǵ������� =======================

	if (KEYMANAGER->isToggleKey(VK_F3)) 
		TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
