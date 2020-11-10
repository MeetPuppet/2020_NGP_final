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

	HRESULT init();		//초기화 함수
	void update();		//연산 함수
	void render();		//그려주는 함수(a.k.a WM_PAINT)

	void KeySet();
};


