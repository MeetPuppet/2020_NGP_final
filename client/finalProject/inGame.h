#pragma once
#include "gameNode.h"

class playerNode;
class enemyNode;
class Bullet;
class Drone;

class inGame :
	public gameNode
{
private:
	playerNode* playernode;
	enemyNode* enemynode;
	Bullet* bullet;
	Drone* drone;
public:
	inGame();
	~inGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


};

