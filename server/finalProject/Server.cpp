
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
	Player1.Activate(&listen_sock);
	Player2.Activate(&listen_sock);
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
				break;
			}
		}
		//Enemy
		else {
			switch (PublicRecvQueue.front().data)
			{
			case CLIENT_PLAYER_NONE:
				actValue = OM->getPlayer2()->changeState(0);
				Player2.SendActValue(actValue);
				actValue.infoType = ENEMY_PLAYER_STATE;
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player1.SendActValue(actValue);
				break;
			case CLIENT_PLAYER_LEFT:
				actValue = OM->getPlayer2()->changeState(1);
				Player2.SendActValue(actValue);
				actValue.infoType = ENEMY_PLAYER_STATE;
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player1.SendActValue(actValue);
				break;
			case CLIENT_PLAYER_RIGHT:
				actValue = OM->getPlayer2()->changeState(2);
				Player2.SendActValue(actValue);
				actValue.infoType = ENEMY_PLAYER_STATE;
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player1.SendActValue(actValue);
				break;
			case CLIENT_PLAYER_SHOT:
				actValue = OM->SpawnEnemyBullet(OM->getPlayer2()->getPoint());
				Player2.SendActValue(actValue);
				actValue.infoType = SPAWN_ENEMY_BULLET;
				actValue.pointX = WINSIZEX - actValue.pointX;
				Player1.SendActValue(actValue);
				break;
			case CLIENT_PLAYER_DRONE:
				break;
			}
		}
		PublicRecvQueue.pop();

	}
	mlock.unlock();
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
	mThread = thread(&RecvThread, this);
}

DWORD WINAPI ServerClientSocket::RecvThread(LPVOID clientSock)
{
	mlock.lock();
	ServerClientSocket* scs = (ServerClientSocket*)clientSock;
	int addrlen = sizeof(SOCKADDR_IN);
	scs->socket = accept((SOCKET)listen,
		(SOCKADDR*)&scs->clientaddr, &addrlen);
	scs->isPlay = true;
	scs->buf = NULL;
	mlock.unlock();

	while (scs->isPlay) {
		scs->recvn(scs->socket, &scs->buf, sizeof(char), NULL);

		mlock.lock();
		scs->RecvQueue->emplace(ClientRequest{ scs->id, scs->buf });
		mlock.unlock();

		scs->buf = NULL;
	}

	return 0;
}

void ServerClientSocket::SendActValue(ActValue actvalue)
{
	//일단 준비만
	//SendQueue.emplace(actvalue);
	
	int buf = *(reinterpret_cast<int*>(&actvalue)) | 0xffffffff;

	send(socket, (char*)buf, sizeof(ActValue), 0);
}


