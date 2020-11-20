#include "playerNode.h"
#include "ControlCode.h"

#define WIDTH 75  //이미지 가로길이
#define HEIGHT 80 //이미지 세로길이


playerNode::playerNode()//무슨일이 벌어질지 모르니 설정해둠
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
		point.x -= 200 * TIMEMANAGER->getElapsedTime();
		break;
	case PS_RIGHT:
		point.x += 200 * TIMEMANAGER->getElapsedTime();
		break;
	}
}

void playerNode::render() 
{
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	img->render(getMemDC(), rc.left, rc.top);


	char str[255];
	wsprintf(str, "X : %d", rc.left);
	TextOut(getMemDC(), point.x, point.y, str, strlen(str));
}

void playerNode::changeState(int state)
{
	switch (state)
	{
	case 0:
		m_state = PS_IDLE;
		break;
	case 1:
		m_state = PS_LEFT;
		break;
	case 2:
		m_state = PS_RIGHT;
		break;
	}
}

void playerNode::keyset()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && m_state != PS_LEFT)
	{
		CLIENT->setSendQueue(CLIENT_PLAYER_LEFT);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && m_state != PS_RIGHT)
	{
		CLIENT->setSendQueue(CLIENT_PLAYER_RIGHT);
	}
	if ((KEYMANAGER->isOnceKeyDown(VK_LEFT) && m_state == PS_RIGHT) ||
		(KEYMANAGER->isOnceKeyDown(VK_RIGHT) && m_state == PS_LEFT))
	{
		CLIENT->setSendQueue(CLIENT_PLAYER_NONE);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		CLIENT->setSendQueue(CLIENT_PLAYER_NONE);
	}
}
