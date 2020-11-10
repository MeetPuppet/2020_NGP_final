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
	//게임노드는 3개의 함수를 반드시 작성해야함
	//HRESULT는 그냥 잘 돌았는지 판단하기 위해서 사용하는것
	virtual HRESULT init(image* IMG, Point p);//클래스 초기화용 할당시 해줘도 좋지만 이해를 돕기위해 init을 쓰기를 권장함

	virtual void update();//말 그대로 업데이트를 담당하는 함수

	virtual void render();//그림을 그려주는 함수
	//이미 메인게임에서 싱글톤(전역으로 이해하면됨)으로 게임노드에서 돌고있으니
	//gameNode::init()같은걸 안에서 돌려줄 필요는 없음

	int getX() { return point.x; }
	Point getPoint() { return point; }
	PLAYERSTATE getState() { return state; }
	PLAYERMOD getMode() { return mode; }
	float getSpeed() { return speed; }
	float getJP() { return jumpPower; }
	RECT getRect() { return rc; }
	RECT getFoot() { return foot; }


};

