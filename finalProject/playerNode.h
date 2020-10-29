#pragma once
#include "gameNode.h"

enum PLAYERSTATE {
	PS_IDLE,
	PS_MOVE,
	PS_BREAK,
	PS_JUMP,
	PS_SIT,
	PS_DEAD
};

enum PLAYERMOD {
	PM_SMALL,
	PM_BIG,
	PM_FIRE
};


class playerNode :
	public gameNode
{
protected:
	image* img;
	
	RECT rc;
	RECT foot;
	Point point;
	RECT CollisionRC;

	RECT checkPos[2];
	int tileIndex[2] = { 0 };

	int IFS;
	float IFF;

	float time;
	float speed;
	float jumpPower;

	PLAYERSTATE state;
	PLAYERMOD mode;

	int frameX;
	int frameY;
	float frameCount;

public:
	playerNode();
	~playerNode();
	//���ӳ��� 3���� �Լ��� �ݵ�� �ۼ��ؾ���
	//HRESULT�� �׳� �� ���Ҵ��� �Ǵ��ϱ� ���ؼ� ����ϴ°�
	virtual HRESULT init(image* IMG, Point p);//Ŭ���� �ʱ�ȭ�� �Ҵ�� ���൵ ������ ���ظ� �������� init�� ���⸦ ������

	virtual void update();//�� �״�� ������Ʈ�� ����ϴ� �Լ�

	virtual void render();//�׸��� �׷��ִ� �Լ�
	//�̹� ���ΰ��ӿ��� �̱���(�������� �����ϸ��)���� ���ӳ�忡�� ����������
	//gameNode::init()������ �ȿ��� ������ �ʿ�� ����

	int getX() { return point.x; }
	Point getPoint() { return point; }
	PLAYERSTATE getState() { return state; }
	PLAYERMOD getMode() { return mode; }
	float getSpeed() { return speed; }
	float getJP() { return jumpPower; }
	RECT getRect() { return rc; }
	RECT getFoot() { return foot; }


};

