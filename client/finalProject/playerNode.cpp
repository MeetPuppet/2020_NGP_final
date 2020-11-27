#include "playerNode.h"
#include "ControlCode.h"
#include "Bullet.h"
#include "Drone.h"

#define WIDTH 75  //이미지 가로길이
#define HEIGHT 80 //이미지 세로길이
#define VK_Z 0x5A
#define VK_X 0x58
#define MAX_SHOT_BULLET_COUNT 10
#define MAX_SHOT_DRONE_COUNT 3

playerNode::playerNode()//무슨일이 벌어질지 모르니 설정해둠
{
	img = NULL;
	HP = 0;
	rc = { 0,0,0,0 };
	point = Point(0.f, 0.f);


	m_state = PS_IDLE;	
}


playerNode::~playerNode()
{

}

HRESULT playerNode::init(image* IMG, Point p, int life)
{			
	img = IMG;
	point = p;
	HP = life;
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);
	
	m_state = PS_IDLE;
	player_bullet_vector.clear();
	player_drone_vector.clear();

	return S_OK;
}

void playerNode::update() 
{
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);
	StateMove();
	keyset();

	for (int i = 0; i < player_bullet_vector.size(); i++)
	{
		player_bullet_vector[i]->update();
	}
	for (int i = 0; i < player_drone_vector.size(); i++)
	{
		player_drone_vector[i]->update();
	}
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
	if (KEYMANAGER->isToggleKey(VK_F3)) {
		Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	}
	for (int i = 0; i < player_drone_vector.size(); i++)
	{
		player_drone_vector[i]->render();
	}

	for (int i = 0; i < player_bullet_vector.size(); i++)
	{
		player_bullet_vector[i]->render();
	}

	for (int i = 0; i < HP; i++)
	{
		IMAGEMANAGER->findImage("life")->render(getMemDC(), 5 * (i + 1) + i * 25, WINSIZEY - 30);
	}

	for (int i = 0; i < MAX_SHOT_BULLET_COUNT - player_bullet_vector.size(); i++)
	{
		IMAGEMANAGER->addImage("player_bullet", "res/player_bullet.bmp", 16, 24, true, RGB(255, 0, 255))->render(getMemDC(), WINSIZEX - (5 * (i + 1)) - (16 * (i + 1)), WINSIZEY - 30);
	}

	for (int i = 0; i < MAX_SHOT_DRONE_COUNT - player_drone_vector.size(); i++)
	{
		IMAGEMANAGER->addImage("player_drone", "res/drone.bmp", 55, 60, true, RGB(255, 0, 255))->render(getMemDC(), WINSIZEX - (5 * (i + 1)) - (55 * (i + 1)), WINSIZEY - 100);
	}

	img->render(getMemDC(), rc.left, rc.top);

	if (KEYMANAGER->isToggleKey(VK_F3)) {
		char str[255];
		int x = point.x;
		wsprintf(str, "%d, %d", x, HP);
		TextOut(getMemDC(), point.x - 20, point.y, str, strlen(str));
	}
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

void playerNode::lose_HP(int damage)
{
	if (HP > 0)
	{
		HP -= damage;
		if (HP < 0)
		{
			HP = 0;
		}
	}
}

void playerNode::keyset()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && KEYMANAGER->isStayKeyDown(VK_RIGHT) && m_state != PS_IDLE)
	{		
		CLIENT->setSendQueue(CLIENT_PLAYER_NONE);
	}
	else if (!KEYMANAGER->isStayKeyDown(VK_LEFT) && KEYMANAGER->isStayKeyDown(VK_RIGHT) && m_state != PS_RIGHT)
	{
		CLIENT->setSendQueue(CLIENT_PLAYER_RIGHT);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT) && m_state != PS_LEFT)
	{
		CLIENT->setSendQueue(CLIENT_PLAYER_LEFT);
	}
	else if (!KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT) && m_state != PS_IDLE)
	{
		CLIENT->setSendQueue(CLIENT_PLAYER_NONE);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_Z) && player_bullet_vector.size() < MAX_SHOT_BULLET_COUNT)
	{
		CLIENT->setSendQueue(CLIENT_PLAYER_SHOT);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_X) && player_drone_vector.size() < MAX_SHOT_DRONE_COUNT)
	{
		CLIENT->setSendQueue(CLIENT_PLAYER_DRONE);
	}
}

void playerNode::spawn_bullet()
{
	Bullet* bullet = new Bullet();
	bullet->init(IMAGEMANAGER->addImage("player_bullet", "res/player_bullet.bmp", 16, 24, true, RGB(255, 0, 255)), Point(point.x, point.y - 40));
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
	Bullet* bullet = player_bullet_vector[id];
	player_bullet_vector.erase(player_bullet_vector.begin() + id);
	delete bullet;
}

void playerNode::erase_drone(int id)
{
	Drone* drone = player_drone_vector[id];
	player_drone_vector.erase(player_drone_vector.begin() + id);
	delete drone;
}