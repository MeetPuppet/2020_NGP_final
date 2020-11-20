#pragma once
#include "gameNode.h"

class playerNode;
class enemyNode;
class Bullet;

class mainGame : public gameNode//2D �����ӿ�ũ ��κ��� ��忡�� ���� ���ư�
{
private:
	playerNode* playernode;
	enemyNode* enemynode;
	Bullet* bullet;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	mainGame();
	~mainGame();
};

