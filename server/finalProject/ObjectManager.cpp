#include "stdafx.h"
#include "ObjectManager.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "Drone.h"
#include "EnemyDrone.h"
#include "collision.h"
#include "playerNode.h"

using namespace HEXA_UTIL;

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
	vDrone.clear();
	vEnemyDrone.clear();

	return S_OK;
}

void ObjectManager::update()
{
	ActValue actValue;

	//업데이트
	for (int i = 0; i < vBullet.size(); ++i) {
		vBullet[i]->update();
		if (vBullet[i]->getRect().bottom <= 0) {
			actValue = EraseBullet(i);
			SERVER->getPlayer1Sock()->SendActValue(actValue);
			actValue.infoType = ERASE_ENEMY_BULLET;
			actValue.pointX = WINSIZEX - actValue.pointX;
			SERVER->getPlayer2Sock()->SendActValue(actValue);
		}
	}
	for (int i = 0; i < vEnemyBullet.size(); ++i) {
		vEnemyBullet[i]->update();
		if (vEnemyBullet[i]->getRect().top >= 800) {
			actValue = EraseEnemyBullet(i);
			SERVER->getPlayer2Sock()->SendActValue(actValue);
			actValue.infoType = ERASE_ENEMY_BULLET;
			actValue.pointX = WINSIZEX - actValue.pointX;
			SERVER->getPlayer1Sock()->SendActValue(actValue);
		}
	}

	for (int i = 0; i < vDrone.size(); ++i) {
		vDrone[i]->update();
		if (vDrone[i]->getRect().bottom <= 0) {
			actValue = EraseDrone(i); 
			actValue.infoType = OVER_WINDOW_PLAYER_DRONE;
			SERVER->getPlayer1Sock()->SendActValue(actValue);
			actValue.infoType = OVER_WINDOW_ENEMY_DRONE;
			actValue.pointX = WINSIZEX - actValue.pointX;
			SERVER->getPlayer2Sock()->SendActValue(actValue);
			//loseHP
			p1->loseHP(2);
		}
	}
	for (int i = 0; i < vEnemyDrone.size(); ++i) {
		vEnemyDrone[i]->update();
		if (vEnemyDrone[i]->getRect().top >= 800) {
			actValue = EraseEnemyDrone(i);
			actValue.infoType = OVER_WINDOW_PLAYER_DRONE;
			SERVER->getPlayer2Sock()->SendActValue(actValue);
			actValue.infoType = OVER_WINDOW_ENEMY_DRONE;
			actValue.pointX = WINSIZEX - actValue.pointX;
			SERVER->getPlayer1Sock()->SendActValue(actValue);
			//loseHP
			p1->loseHP(2);
		}
	}

	//총알 드론
	for (int j = 0; j < vEnemyDrone.size(); ++j) {
		for (int i = 0; i < vBullet.size(); ++i) {
			if (isCollisionReaction(vEnemyDrone[j]->getRect(), vBullet[i]->getRect())) {
				actValue = EraseEnemyDroneBullet(j, i);
				SERVER->getPlayer2Sock()->SendActValue(actValue);
				actValue.infoType = ENEMY_DRONE_AND_PLAYER_BULLET;
				SERVER->getPlayer1Sock()->SendActValue(actValue);
				break;
			}
		}
	}
	for (int j = 0; j < vDrone.size(); ++j) {
		for (int i = 0; i < vEnemyBullet.size(); ++i) {
			if (isCollisionReaction(vDrone[j]->getRect(), vEnemyBullet[i]->getRect())) {
				//send
				actValue = EraseDroneEnemyBullet(j, i);
				SERVER->getPlayer1Sock()->SendActValue(actValue);
				actValue.infoType = ENEMY_DRONE_AND_PLAYER_BULLET;
				SERVER->getPlayer2Sock()->SendActValue(actValue);
				break;
			}
		}
	}

	//1p가 총알 충돌
	for (int i = 0; i < vEnemyBullet.size(); ++i) {
		if (isCollisionReaction(p1->getRect(), vEnemyBullet[i]->getRect())) {
			//send
			actValue = EraseEnemyBullet(i);
			actValue.infoType = PLAYER_BULLET_COLLISION;
			SERVER->getPlayer2Sock()->SendActValue(actValue);
			actValue.infoType = ENEMY_BULLET_COLLISION;
			actValue.pointX = WINSIZEX - actValue.pointX;
			SERVER->getPlayer1Sock()->SendActValue(actValue);
			//loseHP
			p1->loseHP(1);
			break;
		}
	}
	//2p가 총알 충돌
	for (int i = 0; i < vBullet.size(); ++i) {
		if (isCollisionReaction(p2->getRect(), vBullet[i]->getRect())) {
			//send
			actValue = EraseBullet(i);
			actValue.infoType = PLAYER_BULLET_COLLISION;
			SERVER->getPlayer1Sock()->SendActValue(actValue);
			actValue.infoType = ENEMY_BULLET_COLLISION;
			actValue.pointX = WINSIZEX - actValue.pointX;
			SERVER->getPlayer2Sock()->SendActValue(actValue);
			//loseHP
			p2->loseHP(1);
			break;
		}

	}
	//1p가 드론 충돌
	for (int i = 0; i < vEnemyDrone.size(); ++i) {
		if (isCollisionReaction(p1->getRect(), vEnemyDrone[i]->getRect())) {
			//send
			actValue = EraseEnemyDrone(i);
			actValue.infoType = PLAYER_DRONE_COLLISION;
			SERVER->getPlayer2Sock()->SendActValue(actValue);
			actValue.infoType = ENEMY_DRONE_COLLISION;
			actValue.pointX = WINSIZEX - actValue.pointX;
			SERVER->getPlayer1Sock()->SendActValue(actValue);
			//loseHP
			p1->loseHP(2);
			break;
		}
	}
	//2p가 드론 충돌
	for (int i = 0; i < vDrone.size(); ++i) {
		if (isCollisionReaction(p2->getRect(), vDrone[i]->getRect())) {
			//send
			actValue = EraseDrone(i);
			actValue.infoType = PLAYER_DRONE_COLLISION;
			SERVER->getPlayer1Sock()->SendActValue(actValue);
			actValue.infoType = ENEMY_DRONE_COLLISION;
			actValue.pointX = WINSIZEX - actValue.pointX;
			SERVER->getPlayer2Sock()->SendActValue(actValue);
			p2->loseHP(2);
			break;
		}

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
	for (int i = 0; i < vDrone.size(); ++i) {
		vDrone[i]->render();
	}
	for (int i = 0; i < vEnemyDrone.size(); ++i) {
		vEnemyDrone[i]->render();
	}
}

ActValue ObjectManager::SpawnBullet(Point p)
{
	ActValue actvalue;
	actvalue.infoType = SPAWN_PLAYER_BULLET;

	p.y -= 40;
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

	p.y += 40;
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

ActValue ObjectManager::SpawnDrone(Point p)
{
	ActValue actvalue;
	actvalue.infoType = SPAWN_PLAYER_DRONE;

	p.y = WINSIZEY + 50;
	Drone* d = new Drone();
	d->init(p);
	vDrone.emplace_back(d);
	actvalue.infoOption = vEnemyBullet.size();
	actvalue.pointX = p1->getPoint().x;

	return actvalue;
}

ActValue ObjectManager::SpawnEnemyDrone(Point p)
{
	ActValue actvalue;
	actvalue.infoType = SPAWN_PLAYER_DRONE;

	p.y = -50;
	EnemyDrone* d = new EnemyDrone();
	d->init(p);
	vEnemyDrone.emplace_back(d);
	actvalue.infoOption = vEnemyBullet.size();
	actvalue.pointX = p2->getPoint().x;

	return actvalue;
}

ActValue ObjectManager::EraseDrone(int id)
{
	ActValue actvalue;
	actvalue.infoType = ERASE_PLAYER_DRONE;
	actvalue.infoOption = id;
	actvalue.pointX = p1->getPoint().x;

	Drone* d = vDrone[id];
	delete d;
	vDrone.erase(vDrone.begin() + id);

	return actvalue;
}

ActValue ObjectManager::EraseEnemyDrone(int id)
{
	ActValue actvalue;
	actvalue.infoType = ERASE_PLAYER_DRONE;
	actvalue.infoOption = id;
	actvalue.pointX = p2->getPoint().x;

	EnemyDrone* d = vEnemyDrone[id];
	delete d;
	vEnemyDrone.erase(vEnemyDrone.begin() + id);

	return actvalue;
}

ActValue ObjectManager::EraseDroneEnemyBullet(int DroneId, int BulletId)
{
	ActValue actvalue;
	actvalue.infoType = PLAYER_DRONE_AND_ENEMY_BULLET;
	actvalue.infoOption = DroneId;
	actvalue.pointX = BulletId;

	Drone* d = vDrone[DroneId];
	vDrone.erase(vDrone.begin() + DroneId);
	delete d;

	EnemyBullet* b = vEnemyBullet[BulletId];
	vEnemyBullet.erase(vEnemyBullet.begin() + BulletId);
	delete b;

	return actvalue;
}

ActValue ObjectManager::EraseEnemyDroneBullet(int DroneId, int BulletId)
{
	ActValue actvalue;
	actvalue.infoType = PLAYER_DRONE_AND_ENEMY_BULLET;
	actvalue.infoOption = DroneId;
	actvalue.pointX = BulletId;

	EnemyDrone* d = vEnemyDrone[DroneId];
	vEnemyDrone.erase(vEnemyDrone.begin() + DroneId);
	delete d;

	Bullet* b = vBullet[BulletId];
	vBullet.erase(vBullet.begin() + BulletId);
	delete b;

	return actvalue;

}
