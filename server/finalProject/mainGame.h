#pragma once
#include "gameNode.h"

class PlayerBottom;
class PlayerTop;
class ObjectManager;

class mainGame : public gameNode//2D �����ӿ�ũ ��κ��� ��忡�� ���� ���ư�
{
private:
	PlayerBottom* P1;
	PlayerTop* P2;

	ObjectManager* objectManager;
public:
	virtual HRESULT init();			
	virtual void release();			
	virtual void update();			
	virtual void render();	


	mainGame();
	~mainGame();
};

