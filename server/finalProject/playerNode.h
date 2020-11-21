#pragma once
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
	int HP;
	
	RECT rc;
	Point point;

	PLAYERSTATE state;

public:
	playerNode();
	~playerNode();
	//게임노드는 3개의 함수를 반드시 작성해야함
	//HRESULT는 그냥 잘 돌았는지 판단하기 위해서 사용하는것
	HRESULT init(image* IMG, Point p);//클래스 초기화용 할당시 해줘도 좋지만 이해를 돕기위해 init을 쓰기를 권장함

	void update();//말 그대로 업데이트를 담당하는 함수
	void StateMove();
	void render();//그림을 그려주는 함수
	//이미 메인게임에서 싱글톤(전역으로 이해하면됨)으로 게임노드에서 돌고있으니
	//gameNode::init()같은걸 안에서 돌려줄 필요는 없음

	ActValue changeState(int state);
	Point getPoint() { return point; }
	void setPointX(int x) { point.x = x; }
	RECT getRect() { return rc; }

	void loseHP(int value) { HP -= value; }
};

