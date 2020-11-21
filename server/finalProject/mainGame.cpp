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

HRESULT mainGame::init()			//초기화 함수
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

void mainGame::release()			//메모리 해제 함수
{
	gameNode::release();

}

void mainGame::update()				//연산 함수
{
	gameNode::update();

	P1->update();
	P2->update();
	objectManager->update();
}

void mainGame::render()		//그려주는 함수(a.k.a WM_PAINT)
{
	//흰색 도화지 한장~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== 건들지마라 ======================

	P1->render();
	P2->render();
	objectManager->render();




	//==================== 건들지마라 =======================

	if (KEYMANAGER->isToggleKey(VK_F3)) 
		TIMEMANAGER->render(getMemDC());
	

	if (KEYMANAGER->isToggleKey(VK_F1)) {
		char buf[20] = { NULL };
		wsprintf(buf, "Recv");
		TextOut(getMemDC(), 600, 0, buf, strlen(buf));
		for (int i = 0; i < SERVER->getRecvLog()->size(); ++i) {
			char str[20];
			switch ((*SERVER->getRecvLog())[i])
			{
			case 0:
				memcpy(str, "정지", sizeof("정지"));
				break;
			case 1:
				memcpy(str, "왼쪽", sizeof("왼쪽"));
				break;
			case 2:
				memcpy(str, "오른쪽", sizeof("오른쪽"));
				break;
			}
			wsprintf(buf, "%d - %s", i, str);
			TextOut(getMemDC(), 600, i * 16 + 32, buf, strlen(buf));
		}
		wsprintf(buf, "Send");
		TextOut(getMemDC(), 520, 0, buf, strlen(buf));
		for (int i = 0; i < SERVER->getSendLog()->size(); ++i) {
			char str[20];
			switch ((*SERVER->getSendLog())[i])
			{
			case 0:
				memcpy(str, "정지", sizeof("정지"));
				break;
			case 1:
				memcpy(str, "왼쪽", sizeof("왼쪽"));
				break;
			case 2:
				memcpy(str, "오른쪽", sizeof("오른쪽"));
				break;
			}
			wsprintf(buf, "%d - %s", i, str);
			TextOut(getMemDC(), 520, i * 16 + 32, buf, strlen(buf));
		}
	}
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
