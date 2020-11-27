#pragma once
#include "gameNode.h"

class playerNode;
class enemyNode;

class ending :
	public gameNode
{
private:
	playerNode* playernode;
	enemyNode* enemynode;
public:
	ending();
	~ending();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

