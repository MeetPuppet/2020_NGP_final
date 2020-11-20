#include "playerNode.h"
#include "ControlCode.h"
#include "Bullet.h"
#include "Drone.h"

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
	if ((KEYMANAGER->isOnceKeyUp(VK_LEFT) && m_state == PS_LEFT) ||
		(KEYMANAGER->isOnceKeyUp(VK_RIGHT) && m_state == PS_RIGHT))
	{
		CLIENT->setSendQueue(CLIENT_PLAYER_NONE);
	}
	if ((GetKeyState(VK_LEFT) && 0x8001) && KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		CLIENT->setSendQueue(CLIENT_PLAYER_LEFT);
	}
	if ((GetKeyState(VK_RIGHT) && 0x8001) && KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		CLIENT->setSendQueue(CLIENT_PLAYER_RIGHT);
	}
	if (KEYMANAGER->isOnceKeyDown('z' | 'Z'))
	{
		CLIENT->setSendQueue(CLIENT_PLAYER_SHOT);
	}
	if (KEYMANAGER->isOnceKeyDown('x' | 'X'))
	{
		CLIENT->setSendQueue(CLIENT_PLAYER_DRONE);
	}
}

void playerNode::spawn_bullet()
{
	Bullet* bullet = new Bullet();
	bullet->init(IMAGEMANAGER->addImage("player_bullet", "res/player_bullet.bmp", 16, 24, true, RGB(255, 255, 255)), Point(point.x, point.y - 40));
	player_bullet_vector.push_back(bullet);	
}

void playerNode::spawn_drone()
{
	Drone* drone = new Drone();
	drone->init(IMAGEMANAGER->addImage("player_drone", "res/drone.bmp", 55, 60, true, RGB(255, 0, 255)), Point(point.x, WINSIZEY + 50));
	player_drone_vector.push_back(drone);
}

void playerNode::erase_bullet(int id)
{
	Bullet* bullet = &player_bullet_vector[id];
	player_bullet_vector.erase(id);
	delete bullet;
}

void playerNode::erase_drone(int id)
{
	Drone* drone = &player_drone_vector[id];
	player_drone_vector.erase(id);
	delete drone;
}