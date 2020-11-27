#include "stdafx.h"//매니저가 여기에 다 몰려있으니 필요함
#include "playerNode.h"
#include "ControlCode.h"

#define WIDTH 75  //이미지 가로길이
#define HEIGHT 80 //이미지 세로길이


playerNode::playerNode()//무슨일이 벌어질지 모르니 설정해둠
{
	img = NULL;

	rc = { 0,0,0,0 };
	point = Point(0.f, 0.f);


	state = PS_IDLE;
	
}


playerNode::~playerNode()
{

}

HRESULT playerNode::init(image* IMG, Point p)
{			
	HP = 5;
	img = IMG;
	point = p;
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);
	
	state = PS_IDLE;


	return S_OK;
}

void playerNode::update() 
{
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);
	StateMove();
}

void playerNode::StateMove()
{
	switch (state)
	{
	case PS_IDLE:
		break;
	case PS_LEFT:
		if (rc.left > 0) {
			point.x -= MOVE_SPEED * TIMEMANAGER->getElapsedTime();
		}
		else {
			point.x -= rc.left;
		}
		break;
	case PS_RIGHT:
		if (rc.right < WINSIZEX) {
			point.x += MOVE_SPEED * TIMEMANAGER->getElapsedTime();
		}
		else {
			point.x -= rc.right - WINSIZEX;
		}
		break;
	}
}

void playerNode::render() 
{
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	img->render(getMemDC(), rc.left, rc.top);

}
ActValue playerNode::changeState(int state)
{
	ActValue actvalue;
	actvalue.infoType = PLAYER_STATE;

	switch (state)
	{
	case 0:
		playerNode::state = PS_IDLE;
		actvalue.infoOption = 0;
		break;
	case 1:
		playerNode::state = PS_LEFT;
		actvalue.infoOption = 1;
		break;
	case 2:
		playerNode::state = PS_RIGHT;
		actvalue.infoOption = 2;
		break;
	}

	actvalue.pointX = (unsigned short)point.x;

	return actvalue;
}