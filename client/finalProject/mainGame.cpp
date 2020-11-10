#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}

mainGame::~mainGame()
{

}

HRESULT mainGame::init()			//�ʱ�ȭ �Լ�
{
	gameNode::init(true);

	SCENEMANAGER->changeScene("title");

	return S_OK;
}

void mainGame::release()			//�޸� ���� �Լ�
{
	gameNode::release();
	//delete p;//�Ҵ� ����
	//delete q;
	SCENEMANAGER->release();
}

void mainGame::update()				//���� �Լ�
{
	gameNode::update();

	SCENEMANAGER->update();
}

void mainGame::render()		//�׷��ִ� �Լ�(a.k.a WM_PAINT)
{
	//��� ��ȭ�� ����~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== �ǵ������� ======================

	SCENEMANAGER->render();

	//==================== �ǵ������� =======================

	if (KEYMANAGER->isToggleKey(VK_F3)) 
		TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
