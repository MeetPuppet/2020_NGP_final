#include "enemyNode.h"
#include "ControlCode.h"
#include "Bullet.h"
#include "Drone.h"

#define WIDTH 75  //이미지 가로길이
#define HEIGHT 80 //이미지 세로길이
#define MAX_SHOT_BULLET_COUNT 10
#define MAX_SHOT_DRONE_COUNT 3
#define SPEED 200


enemyNode::enemyNode()//무슨일이 벌어질지 모르니 설정해둠
{
	img = NULL;
	HP = 0;
	rc = { 0,0,0,0 };
	point = Point(0.f, 0.f);


	m_state = EPS_IDLE;

}


enemyNode::~enemyNode()
{

}

HRESULT enemyNode::init(image* IMG, Point p, int life)
{
	img = IMG;
	point = p;
	HP = life;
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);

	m_state = EPS_IDLE;
	enemy_bullet_vector.clear();
	enemy_drone_vector.clear();

	return S_OK;
}

void enemyNode::update()
{
	rc = RectMakeCenter(point.x, point.y, WIDTH, HEIGHT);
	StateMove();

	for (int i = 0; i < enemy_bullet_vector.size(); i++)
	{
		enemy_bullet_vector[i]->enemy_update();
	}
	for (int i = 0; i < enemy_drone_vector.size(); i++)
	{
		enemy_drone_vector[i]->enemy_update();
	}
}

void enemyNode::StateMove()
{
	switch (m_state)
	{
	case EPS_IDLE:
		break;
	case EPS_LEFT:
		point.x += SPEED * TIMEMANAGER->getElapsedTime();
		if (point.x > WINSIZEX - (float)WIDTH / 2.f)
		{
			point.x = WINSIZEX - (float)WIDTH / 2.f;
		}
		break;
	case EPS_RIGHT:
		point.x -= SPEED * TIMEMANAGER->getElapsedTime();
		if (point.x < (float)WIDTH / 2.f)
		{
			point.x = (float)WIDTH / 2.f;
		}
		break;
	}
}

void enemyNode::render()
{
	if (KEYMANAGER->isToggleKey(VK_F3)) {
		Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	}

	for (int i = 0; i < enemy_drone_vector.size(); i++)
	{
		enemy_drone_vector[i]->render();
	}

	for (int i = 0; i < enemy_bullet_vector.size(); i++)
	{
		enemy_bullet_vector[i]->render();
	}

	for (int i = 0; i < HP; i++)
	{
		IMAGEMANAGER->findImage("life")->render(getMemDC(), 5 * (i + 1) + i * 25, 0);
	}

	for (int i = 0; i < MAX_SHOT_BULLET_COUNT - enemy_bullet_vector.size(); i++)
	{
		IMAGEMANAGER->findImage("enemy_bullet")->render(getMemDC(), WINSIZEX - (5 * (i + 1)) - (16 * (i + 1)), 5);
	}

	for (int i = 0; i < MAX_SHOT_DRONE_COUNT - enemy_drone_vector.size(); i++)
	{
		IMAGEMANAGER->findImage("enemy_drone")->render(getMemDC(), WINSIZEX - (5 * (i + 1)) - (55 * (i + 1)), 40);
	}

	img->render(getMemDC(), rc.left, rc.top);

	if (KEYMANAGER->isToggleKey(VK_F3)) {
		char str[255];
		int x = point.x;
		wsprintf(str, "%d, %d", x, HP);
		TextOut(getMemDC(), point.x-20, point.y, str, strlen(str));
	}
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

void enemyNode::lose_HP(int damage)
{
	SOUNDMANAGER->play("05.hit");
	if (HP > 0)
	{
		HP -= damage;
		if (HP < 0)
		{
			HP = 0;
		}
	}
}

void enemyNode::enemy_spawn_bullet()
{
	SOUNDMANAGER->play("02.shot");
	Bullet* bullet = new Bullet();
	bullet->init(IMAGEMANAGER->addImage("enemy_bullet", "res/enemy_bullet.bmp", 16, 24, true, RGB(255, 0, 255)), Point(point.x, point.y + 40));
	enemy_bullet_vector.push_back(bullet);
}

void enemyNode::enemy_spawn_drone()
{
	SOUNDMANAGER->play("03.drone");
	Drone* drone = new Drone();
	drone->init(IMAGEMANAGER->addImage("enemy_drone", "res/enemy_drone.bmp", 55, 60, true, RGB(255, 0, 255)), Point(point.x, -50));
	enemy_drone_vector.push_back(drone);
}

void enemyNode::enemy_erase_bullet(int id)
{
	Bullet* bullet = enemy_bullet_vector[id];
	enemy_bullet_vector.erase(enemy_bullet_vector.begin() + id);
	delete bullet;
}

void enemyNode::enemy_erase_drone(int id)
{
	Drone* drone = enemy_drone_vector[id];
	enemy_drone_vector.erase(enemy_drone_vector.begin() + id);
	delete drone;
}