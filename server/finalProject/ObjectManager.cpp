#include "stdafx.h"
#include "ObjectManager.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "collision.h"
#include "playerNode.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

HRESULT ObjectManager::init()
{
	vBullet.clear();
	vEnemyBullet.clear();

	return S_OK;
}

void ObjectManager::update()
{
	for (int i = 0; i < vBullet.size(); ++i) {
		vBullet[i]->update();
	}
	for (int i = 0; i < vEnemyBullet.size(); ++i) {
		vEnemyBullet[i]->update();
	}
}

void ObjectManager::render()
{
	for (int i = 0; i < vBullet.size(); ++i) {
		vBullet[i]->render();
	}
	for (int i = 0; i < vEnemyBullet.size(); ++i) {
		vEnemyBullet[i]->render();
	}
}

ActValue ObjectManager::SpawnBullet(Point p)
{
	ActValue actvalue;
	actvalue.infoType = SPAWN_PLAYER_BULLET;

	Bullet* b = new Bullet();
	b->init(p);
	vBullet.emplace_back(b);
	actvalue.infoOption = vBullet.size();
	actvalue.pointX = p1->getPoint().x;

	return actvalue;
}

ActValue ObjectManager::SpawnEnemyBullet(Point p)
{
	ActValue actvalue;
	actvalue.infoType = SPAWN_PLAYER_BULLET;

	EnemyBullet* b = new EnemyBullet();
	b->init(p);
	vEnemyBullet.emplace_back(b);
	actvalue.infoOption = vEnemyBullet.size();
	actvalue.pointX = p2->getPoint().x;

	return actvalue;
}

ActValue ObjectManager::EraseBullet(int id)
{
	ActValue actvalue;
	actvalue.infoType = ERASE_PLAYER_BULLET;
	actvalue.infoOption = id;
	actvalue.pointX = p1->getPoint().x;

	Bullet* b = vBullet[id];
	delete b;
	vBullet.erase(vBullet.begin() + id);

	return actvalue;
}

ActValue ObjectManager::EraseEnemyBullet(int id)
{
	ActValue actvalue;
	actvalue.infoType = ERASE_PLAYER_BULLET;
	actvalue.infoOption = id;
	actvalue.pointX = p2->getPoint().x;

	EnemyBullet* b = vEnemyBullet[id];
	delete b;
	vEnemyBullet.erase(vEnemyBullet.begin() + id);

	return actvalue;
}
