#pragma once
#include "gameNode.h"
class loading :
	public gameNode
{
public:
	loading();
	~loading();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

