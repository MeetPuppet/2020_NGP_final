#pragma once
#include "stdafx.h"//�Ŵ����� ���⿡ �� ���������� �ʿ���
#include "gameNode.h"

enum PLAYERSTATE {
	PS_IDLE,
	PS_LEFT,
	PS_RIGHT
};

class playerNode :
	public gameNode
{
protected:
	image* img;
	
	RECT rc;
	Point point;

	PLAYERSTATE m_state;

public:
	playerNode();
	~playerNode();
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

};

