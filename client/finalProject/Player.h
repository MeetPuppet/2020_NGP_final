#pragma once
#include "gameNode.h"

enum PLAYERSTATE_S {
	PS_IDLE,
	PS_LEFT,
	PS_RIGHT
};

class Player : public gameNode
{
private:
	PLAYERSTATE_S state;
	image* img;
	Point p;
	RECT rc;
public:
	Player();
	~Player();

	HRESULT init();		//�ʱ�ȭ �Լ�
	void update();		//���� �Լ�
	void render();		//�׷��ִ� �Լ�(a.k.a WM_PAINT)

	void KeySet();
};


