#pragma once
#include "gameNode.h"
class title :
	public gameNode
{
public:
	title();
	~title();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

