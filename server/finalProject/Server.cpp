
#include "stdafx.h"
#include "Server.h"
#include "playerNode.h"
#include "ObjectManager.h"
#include <thread>

Server::Server()
{
	OM = nullptr;
}

Server::~Server()
{
}

HRESULT Server::init()
{
	int retval;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return S_FALSE;

	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET)
		return S_FALSE;

	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
		return S_FALSE;

	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
		return S_FALSE;

	Player1.id = 0;
	Player2.id = 1;
	play = true;
	Player1.Activate(&listen_sock);
	Player2.Activate(&listen_sock);
	while (!(Player1.isPlay && Player2.isPlay));
	Player1.SendAirValue();
	Player2.SendAirValue();

	ThreadActivate();
	//vecThread.emplace_back(&Player1.Activate, listen_sock);
	//vecThread.emplace_back(&Player2.Activate, listen_sock);
}

void Server::update()
{
	mlock.lock();
	ActValue actValue;
	while (PublicRecvQueue.size() != 0) {
		//Player
		if (PublicRecvQueue.front().id == 0) {
			switch (PublicRecvQueue.front().data)
			{
			case CLIENT_PLAYER_NONE:
				actValue = OM->getPlayer1()->changeState(0);
				Player1.SendActValue(actValue);
				actValue.infoType = ENEMY_PLAYER_STATE;
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player2.SendActValue(actValue);
				break;
			case CLIENT_PLAYER_LEFT:
				actValue = OM->getPlayer1()->changeState(1);
				Player1.SendActValue(actValue);
				actValue.infoType = ENEMY_PLAYER_STATE;
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player2.SendActValue(actValue);
				break;
			case CLIENT_PLAYER_RIGHT:
				actValue = OM->getPlayer1()->changeState(2);
				Player1.SendActValue(actValue);
				actValue.infoType = ENEMY_PLAYER_STATE;
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player2.SendActValue(actValue);
				break;
			case CLIENT_PLAYER_SHOT:
				actValue = OM->SpawnBullet(OM->getPlayer1()->getPoint());
				Player1.SendActValue(actValue);
				actValue.infoType = SPAWN_ENEMY_BULLET;
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player2.SendActValue(actValue);
				break;
			case CLIENT_PLAYER_DRONE:
				actValue = OM->SpawnDrone(OM->getPlayer1()->getPoint());
				Player1.SendActValue(actValue);
				actValue.infoType = SPAWN_ENEMY_DRONE;
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player2.SendActValue(actValue);
				break;
			}
		}
		//Enemy
		else {
			switch (PublicRecvQueue.front().data)
			{
			case CLIENT_PLAYER_NONE:
				actValue = OM->getPlayer2()->changeState(0);
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player2.SendActValue(actValue);
				actValue.infoType = ENEMY_PLAYER_STATE;
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player1.SendActValue(actValue);
				break;
			case CLIENT_PLAYER_LEFT:
				actValue = OM->getPlayer2()->changeState(1);
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player2.SendActValue(actValue);
				actValue.infoType = ENEMY_PLAYER_STATE;
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player1.SendActValue(actValue);
				break;
			case CLIENT_PLAYER_RIGHT:
				actValue = OM->getPlayer2()->changeState(2);
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player2.SendActValue(actValue);
				actValue.infoType = ENEMY_PLAYER_STATE;
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player1.SendActValue(actValue);
				break;
			case CLIENT_PLAYER_SHOT:
				actValue = OM->SpawnEnemyBullet(OM->getPlayer2()->getPoint());
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player2.SendActValue(actValue);
				actValue.infoType = SPAWN_ENEMY_BULLET;
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player1.SendActValue(actValue);
				break;
			case CLIENT_PLAYER_DRONE:
				actValue = OM->SpawnEnemyDrone(OM->getPlayer2()->getPoint());
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player2.SendActValue(actValue);
				actValue.infoType = SPAWN_ENEMY_DRONE;
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player1.SendActValue(actValue);
				break;
			}
		}
		PublicRecvQueue.pop();

	}
	mlock.unlock();
}

void Server::ThreadActivate()
{
	mThread = thread(&Server::PublicRecvThread, this, this);
}

DWORD WINAPI Server::PublicRecvThread(LPVOID arg)
{
	while (play) {
		if (Player1.localRecvQueue.size() != 0) {
			mlock.lock();
			Player1.localLock.lock();
			PublicRecvQueue.emplace(Player1.localRecvQueue.front());
			Player1.localRecvQueue.pop();
			Player1.localLock.unlock();
			mlock.unlock();
		}

		if (Player2.localRecvQueue.size() != 0) {
			mlock.lock();
			Player2.localLock.lock();
			PublicRecvQueue.emplace(Player2.localRecvQueue.front());
			Player2.localRecvQueue.pop();
			Player2.localLock.unlock();
			mlock.unlock();
		}
	}

	return 0;
}

ServerClientSocket::ServerClientSocket()
{
}

ServerClientSocket::~ServerClientSocket()
{
}

void ServerClientSocket::Activate(SOCKET* listen)
{
	listenSock = listen;

	int addrlen = sizeof(SOCKADDR_IN);
	socket = accept((SOCKET)*listenSock,
		(SOCKADDR*)&clientaddr, &addrlen);
	isPlay = true;
	buf = NULL;

	mThread = thread(&ServerClientSocket::RecvThread, this, this);
}

DWORD WINAPI ServerClientSocket::RecvThread(LPVOID arg)
{
	while (isPlay) {
		recvn(socket, &buf, sizeof(char), NULL);
		if (buf == NULL)
			continue;
		localLock.lock();
		if (RecvLog.size() > 20) {
			RecvLog.erase(RecvLog.begin());
		}
		switch (buf)
		{
		case CLIENT_PLAYER_NONE:
			RecvLog.emplace_back(0);
			break;
		case CLIENT_PLAYER_LEFT:
			RecvLog.emplace_back(1);
			break;
		case CLIENT_PLAYER_RIGHT:
			RecvLog.emplace_back(2);
			break;
		}
		localRecvQueue.emplace(ClientRequest{ id, buf });
		localLock.unlock();
		buf = NULL;
	}

	return 0;
}

void ServerClientSocket::SendActValue(ActValue actvalue)
{
	//일단 준비만
	//SendQueue.emplace(actvalue);
	
	if (SendLog.size() > 20) {
		SendLog.erase(SendLog.begin());
	}
	SendLog.emplace_back(actvalue.infoOption);

	int buf = NULL;
	buf = buf | actvalue.infoType;
	buf = buf << 8;
	buf = buf | actvalue.infoOption;
	buf = buf << 16;
	buf = buf | actvalue.pointX;

	send(socket, (char*)&buf, sizeof(int), 0);

}

void ServerClientSocket::SendAirValue()
{
	char value = 1;
	send(socket, &value, sizeof(char), NULL);
}


