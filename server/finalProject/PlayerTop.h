#pragma once
#include "playerNode.h"
class PlayerTop :
	public playerNode
{
private:
public:
	HRESULT init();

	void update();
	void StateMove();
};

