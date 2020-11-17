#pragma once
#include "gameNode.h"
#include <vector>

class playerNode;
class Bullet;
class EnemyBullet;

class ObjectManager :
	public gameNode
{
private:
	playerNode* p1;
	playerNode* p2;

	vector<Bullet*> vBullet;
	vector<EnemyBullet*> vEnemyBullet;
public:
	ObjectManager();
	~ObjectManager();
	HRESULT init();
	void update();
	void render();

	void LinkToPlayer1(playerNode* player) { p1 = player; }
	playerNode* getPlayer1() { return p1; }
	void LinkToPlayer2(playerNode* player) { p2 = player; }
	playerNode* getPlayer2() { return p2; }

	ActValue SpawnBullet(Point p);
	ActValue SpawnEnemyBullet(Point p);
	ActValue EraseBullet(int id);
	ActValue EraseEnemyBullet(int id);
};
