#include "stdafx.h"
#include "playerNode.h"
#include "enemyNode.h"
#include "Bullet.h"
#include "Drone.h"
#include "inGame.h"

inGame::inGame()
{
	playernode = nullptr;
	enemynode = nullptr;
}

inGame::~inGame()
{
	delete playernode;
	delete enemynode;
}

HRESULT inGame::init()
{
	CLIENT->init();

	SOUNDMANAGER->play("01.start");

	IMAGEMANAGER->addImage("space", "res/background.bmp", 800, 800, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("life", "res/life.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_bullet", "res/player_bullet.bmp", 16, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_drone", "res/drone.bmp", 55, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("enemy_bullet", "res/enemy_bullet.bmp", 16, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("enemy_drone", "res/enemy_drone.bmp", 55, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("explosion", "res/explosion.bmp", 48, 16, 3, 1, true, RGB(255, 0, 255));

	if (playernode != nullptr)
	{
		delete playernode;
	}
	playernode = new playerNode();
	playernode->init(IMAGEMANAGER->addImage("player", "res/player.bmp", 75, 80, true, RGB(255, 0, 255)), Point(WINSIZEX / 2, WINSIZEY / 2 + 350), 5);
	CLIENT->setPlayerRef(playernode);

	if (enemynode != nullptr)
	{
		delete enemynode;
	}
	enemynode = new enemyNode();
	enemynode->init(IMAGEMANAGER->addImage("enemy", "res/enemy_player.bmp", 75, 80, true, RGB(255, 0, 255)), Point(WINSIZEX / 2, WINSIZEY / 2 - 350), 5);
	CLIENT->setEnemyRef(enemynode);

	return S_OK;
}

void inGame::release()
{
}

void inGame::update()
{
	CLIENT->update();
	playernode->update();
	enemynode->update();
}

void inGame::render()
{
	IMAGEMANAGER->findImage("space")->render(getMemDC());
	playernode->render();
	enemynode->render();
}

