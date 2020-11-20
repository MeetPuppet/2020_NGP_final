#include "enemyNode.h"
#include "ControlCode.h"

#define WIDTH 75  //이미지 가로길이
#define HEIGHT 80 //이미지 세로길이


enemyNode::enemyNode()//무슨일이 벌어질지 모르니 설정해둠
{
	img = NULL;

	rc = { 0,0,0,0 };
	point = Point(0.f, 0.f);


	m_state = EPS_IDLE;

}


enemyNode::~enemyNode()
{

}

HRESULT enemyNode::init(image* IMG, Point p)
{
	img = IMG;
	point = p;
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);

	m_state = EPS_IDLE;


	return S_OK;
}

void enemyNode::update()
{
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);
	StateMove();
}

void enemyNode::StateMove()
{
	switch (m_state)
	{
	case EPS_IDLE:
		break;
	case EPS_LEFT:
		point.x += 200 * TIMEMANAGER->getElapsedTime();
		break;
	case EPS_RIGHT:
		point.x -= 200 * TIMEMANAGER->getElapsedTime();
		break;
	}
}

void enemyNode::render()
{
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	img->render(getMemDC(), rc.left, rc.top);


	char str[255];
	wsprintf(str, "X : %d", rc.left);
	TextOut(getMemDC(), point.x, point.y, str, strlen(str));
}

void enemyNode::changeState(int state)
{
	switch (state)
	{
	case 0:
		m_state = EPS_IDLE;
		break;
	case 1:
		m_state = EPS_LEFT;
		break;
	case 2:
		m_state = EPS_RIGHT;
		break;
	}
}