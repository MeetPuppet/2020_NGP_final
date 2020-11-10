#include "stdafx.h"
#include "greyTurtle.h"



greyTurtle::greyTurtle()
{
}


greyTurtle::~greyTurtle()
{
}

HRESULT greyTurtle::init(POINT point)
{
	enemyNode::init("greyTurtle", point);

	return S_OK;
}
void greyTurtle::release()
{
}
void greyTurtle::update()
{
	enemyNode::update();
}
void greyTurtle::render()
{
	enemyNode::render();
}

void greyTurtle::FrameSeter()
{
	switch (state)
	{
	case EL_PATROL:
	case EL_CHASE:
	case ER_PATROL:
	case ER_CHASE:
		if (img->getMaxFrameX() > FrameCheck) {
			FrameCheck += 1 * TIMEMANAGER->getElapsedTime();
			if (FrameCheck >= 2) {
				frameX = 1;
			}
			else
				frameX = FrameCheck;
		}
		else {
			FrameCheck = 0;
			frameX = FrameCheck;
		}
		break;
	case DEAD:
		frameX = 2;
		break;
	}
}

void greyTurtle::AI(POINT* playerPoint)
{
	enemyNode::AI(playerPoint);
}