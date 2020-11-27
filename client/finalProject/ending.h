#pragma once
#include "gameNode.h"

class ending :
	public gameNode
{
private:
	bool isP1;
public:
	ending(bool winner);
	~ending();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

