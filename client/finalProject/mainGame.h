#pragma once
#include "gameNode.h"

class playerNode;
class enemyNode;
class Bullet;

class mainGame : public gameNode//2D 프레임워크 대부분은 노드에서 먼저 돌아감
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

