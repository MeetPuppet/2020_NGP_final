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

HRESULT mainGame::init()			//�ʱ�ȭ �Լ�
{
	gameNode::init(true);

	AddSound();
	SCENEMANAGER->addScene("title", new title);
	SCENEMANAGER->addScene("inGame", new inGame);
	SCENEMANAGER->addScene("ending", new ending);
	SCENEMANAGER->changeScene("title");

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

void mainGame::AddSound()
{
	SOUNDMANAGER->addSound("01.start", "sound/01start.ogg", false, false);
	SOUNDMANAGER->addSound("02.shot", "sound/02shot.ogg", false, false);
	SOUNDMANAGER->addSound("03.drone", "sound/03drone.ogg", false, false);
	SOUNDMANAGER->addSound("04.connect", "sound/04connect.ogg", false, false);
	SOUNDMANAGER->addSound("05.hit", "sound/05hit.ogg", false, false);
}
