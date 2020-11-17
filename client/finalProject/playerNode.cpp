#include "stdafx.h"//�Ŵ����� ���⿡ �� ���������� �ʿ���
#include "playerNode.h"
#include "ControlCode.h"

#define WIDTH 75  //�̹��� ���α���
#define HEIGHT 80 //�̹��� ���α���


playerNode::playerNode()//�������� �������� �𸣴� �����ص�
{
	img = NULL;

	rc = { 0,0,0,0 };
	point = Point(0.f, 0.f);


	m_state = PS_IDLE;
	
}


playerNode::~playerNode()
{

}

HRESULT playerNode::init(image* IMG, Point p)
{			
	img = IMG;
	point = p;
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);
	
	m_state = PS_IDLE;


	return S_OK;
}

void playerNode::update() 
{
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);
	StateMove();
	keyset();
}

void playerNode::StateMove()
{
	switch (m_state)
	{
	case PS_IDLE:
		break;
	case PS_LEFT:
		point.x -= 20 * TIMEMANAGER->getElapsedTime();
		break;
	case PS_RIGHT:
		point.x += 20 * TIMEMANAGER->getElapsedTime();
		break;
	}
}

void playerNode::render() 
{
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	img->render(getMemDC(), rc.left, rc.top);

}

void playerNode::changeState(int state)
{
	ActValue actvalue;
	actvalue.infoType = PLAYER_STATE;

	switch (state)
	{
	case 0:
		m_state = PS_IDLE;
		actvalue.infoOption = 0;
		break;
	case 1:
		m_state = PS_LEFT;
		actvalue.infoOption = 1;
		break;
	case 2:
		m_state = PS_RIGHT;
		actvalue.infoOption = 2;
		break;
	}

	actvalue.pointX = point.x;

	//return actvalue;
}

void playerNode::keyset()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		CLIENT->setSendQueue(CLIENT_PLAYER_LEFT);
		m_state = PS_LEFT;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		CLIENT->setSendQueue(CLIENT_PLAYER_RIGHT);
		m_state = PS_RIGHT;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		CLIENT->setSendQueue(CLIENT_PLAYER_NONE);
		m_state = PS_IDLE;
	}
}
