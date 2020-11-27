#pragma once
#include "gameNode.h"
class ending :
	public gameNode
{
public:
	ending();
	~ending();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

