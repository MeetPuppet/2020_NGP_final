#pragma once
#include "stdafx.h"//�Ŵ����� ���⿡ �� ���������� �ʿ���
#include "gameNode.h"

class Bullet;
class Drone;

enum ENEMYSTATE {
	EPS_IDLE,
	EPS_LEFT,
	EPS_RIGHT
};

class enemyNode :
	public gameNode
{
protected:
	image* img;

	RECT rc;
	Point point;
	vector<Bullet> enemy_bullet_vector;
	vector<Drone> enemy_drone_vector;

	ENEMYSTATE m_state;

public:
	enemyNode();
	~enemyNode();
	//���ӳ��� 3���� �Լ��� �ݵ�� �ۼ��ؾ���
	//HRESULT�� �׳� �� ���Ҵ��� �Ǵ��ϱ� ���ؼ� ����ϴ°�
	HRESULT init(image* IMG, Point p);//Ŭ���� �ʱ�ȭ�� �Ҵ�� ���൵ ������ ���ظ� �������� init�� ���⸦ ������

	void update();//�� �״�� ������Ʈ�� ����ϴ� �Լ�
	void StateMove();
	void render();//�׸��� �׷��ִ� �Լ�
	//�̹� ���ΰ��ӿ��� �̱���(�������� �����ϸ��)���� ���ӳ�忡�� ����������
	//gameNode::init()������ �ȿ��� ������ �ʿ�� ����

	void changeState(int state);
	Point getPoint() { return point; }
	void setPointX(int x) { point.x = x; }
	RECT getRect() { return rc; }

	void keyset();
	void enemy_spawn_bullet();
	void enemy_spawn_drone();
	void enemy_erase_bullet(int id);
	void enemy_erase_drone(int id);
};

