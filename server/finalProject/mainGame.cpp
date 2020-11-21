#include "stdafx.h"
#include "mainGame.h"
#include "PlayerBottom.h"
#include "PlayerTop.h"
#include "ObjectManager.h"

mainGame::mainGame()
{
}

mainGame::~mainGame()
{

}

HRESULT mainGame::init()			//�ʱ�ȭ �Լ�
{
	gameNode::init(true);

	P1 = new PlayerBottom();
	P1->init();
	P2 = new PlayerTop();
	P2->init();

	objectManager = new ObjectManager();
	objectManager->init();
	objectManager->LinkToPlayer1(P1);
	objectManager->LinkToPlayer2(P2);

	SERVER->LinkToObjectManager(objectManager);

	return S_OK;
}

void mainGame::release()			//�޸� ���� �Լ�
{
	gameNode::release();

}

void mainGame::update()				//���� �Լ�
{
	gameNode::update();

	P1->update();
	P2->update();
	objectManager->update();
}

void mainGame::render()		//�׷��ִ� �Լ�(a.k.a WM_PAINT)
{
	//��� ��ȭ�� ����~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== �ǵ������� ======================

	P1->render();
	P2->render();
	objectManager->render();

	//for (int i = 0; i < SERVER->getLog()->size(); ++i) {
	//	char str = (*SERVER->getLog())[i];
	//	wsprintf(buf, "%d", str);
	//	TextOut(getMemDC(), 600, i * 20, buf, strlen(buf));
	//}

	//char buf[20] = { NULL };
	//wsprintf(buf, "%d", SERVER->getPlayer1Sock()->getQueueSize());
	//TextOut(getMemDC(), 600, 10, buf, strlen(buf));
	//wsprintf(buf, "%d", SERVER->getPlayer2Sock()->getQueueSize());
	//TextOut(getMemDC(), 600, 30, buf, strlen(buf));
	//wsprintf(buf, "%d", SERVER->getQueueSize());
	//TextOut(getMemDC(), 600, 50, buf, strlen(buf));
	//==================== �ǵ������� =======================

	if (KEYMANAGER->isToggleKey(VK_F3)) 
		TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
