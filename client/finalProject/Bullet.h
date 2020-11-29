#pragma once
#include "gameNode.h"

class Bullet :	public gameNode
{
private:
	image* img;

	RECT rc;
	Point point;
	int id;
public:
	Bullet();
	~Bullet();

	HRESULT init(image* IMG, Point p);
	void setPlayerBulletID(int no) { id = no; }
	int getPlayerBulletID() { return id; }

	void update();
	void enemy_update();
	void render();
	Point getPoint() { return point; }
};

