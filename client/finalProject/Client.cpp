#include "Client.h"
#include "playerNode.h"
#include "enemyNode.h"
#include "stdafx.h"

Client::Client()
{
}


Client::~Client()
{
}

HRESULT Client::init()
{
	int retval;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return S_FALSE;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		return S_FALSE;

	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.S_un.S_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
		return S_FALSE;

	isPlay = true;
	buf = NULL;

	mthread = thread(&Client::RecvThread, this, this);

}

DWORD WINAPI Client::RecvThread(LPVOID clientSock)
{
	while (isPlay) {
		int recv_data = NULL;
		recvn(sock, (char*)&recv_data, sizeof(int), NULL);
		if (recv_data == NULL)
			continue;

		ActValue act;
		act.pointX = recv_data & 0xffff;
		recv_data = recv_data >> 16;
		act.infoOption = recv_data & 0xff;
		recv_data = recv_data >> 8;
		act.infoType = recv_data & 0xff;


		mlock.lock();
		mRecvQueue.emplace(act);
		mlock.unlock();
	}

	return 0;
}

int recvn(SOCKET s, char* buf, int len, int flags)
{
	int received;
	char* ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);

		if (received == SOCKET_ERROR) {
			return SOCKET_ERROR;
		}
		else if (received == WSAEWOULDBLOCK) {
			return WSAEWOULDBLOCK;
		}
		else if (received == 0) {
			break;
		}
		left -= received;
		ptr += received;
	}
	return (len - left);
}

void Client::update()
{

	mlock.lock();
	while (mSendQueue.size() != 0)
	{
		char send_data = mSendQueue.front();
		send(sock, (char *)&send_data, sizeof(char), 0);
		mSendQueue.pop();
	}

	while (mRecvQueue.size() != 0)
	{
		ActValue act;
		act = mRecvQueue.front();

		//to do
		switch (act.infoType)
		{
		case PLAYER_STATE:
			player->changeState((int)act.infoOption);
			player->setPointX((int)act.pointX);
			break;
		case SPAWN_PLAYER_BULLET:
			player->spawn_bullet();
			break;
		case ERASE_PLAYER_BULLET:
			player->erase_bullet((int)act.infoOption);
			break;
		case SPAWN_PLAYER_DRONE:
			player->spawn_drone();
			break;
		case ERASE_PLAYER_DRONE:
			player->erase_drone((int)act.infoOption);
			break;
		case OVER_WINDOW_PLAYER_DRONE:
			player->erase_drone((int)act.infoOption);
			enemy->lose_HP(2);
			break;
		case PLAYER_BULLET_COLLISION:
			player->erase_bullet((int)act.infoOption);
			enemy->lose_HP(1);
			break;
		case PLAYER_DRONE_COLLISION:
			player->erase_drone((int)act.infoOption);
			enemy->lose_HP(2);
			break;
		case PLAYER_DRONE_AND_ENEMY_BULLET:
			player->erase_drone((int)act.infoOption);
			enemy->enemy_erase_bullet((int)act.pointX);
			break;
		case ENEMY_PLAYER_STATE:
			enemy->changeState((int)act.infoOption);
			enemy->setPointX((int)act.pointX);
			break;
		case SPAWN_ENEMY_BULLET:
			enemy->enemy_spawn_bullet();
			break;
		case ERASE_ENEMY_BULLET:
			enemy->enemy_erase_bullet((int)act.infoOption);
			break;
		case SPAWN_ENEMY_DRONE:
			enemy->enemy_spawn_drone();
			break;
		case ERASE_ENEMY_DRONE:
			enemy->enemy_erase_drone((int)act.infoOption);			
			break;
		case ENEMY_BULLET_COLLISION:
			enemy->enemy_erase_bullet((int)act.infoOption);
			player->lose_HP(1);
			break;
		case ENEMY_DRONE_COLLISION:
			enemy->enemy_erase_drone((int)act.infoOption);
			player->lose_HP(2);
			break;
		case ENEMY_DRONE_AND_PLAYER_BULLET:
			enemy->enemy_erase_drone((int)act.infoOption);
			player->erase_bullet((int)act.pointX);
			break;
		case OVER_WINDOW_ENEMY_DRONE:
			enemy->enemy_erase_drone((int)act.infoOption);
			player->lose_HP(2);
			break;
		case SCENE_CHANGE:
			break;
		}
		mRecvQueue.pop();
	}
	mlock.unlock();
}