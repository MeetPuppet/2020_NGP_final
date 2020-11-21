#pragma once
#include "singletonBase.h"
#include "stdafx.h"//매니저가 여기에 다 몰려있으니 필요함
#include "ControlCode.h"
#include <winsock2.h>
#include <queue>

#pragma comment(lib, "ws2_32")

class playerNode;
class enemyNode;

class Client : public singletonBase<Client>
{
private:
	WSADATA wsa;
	SOCKET sock;
	SOCKADDR_IN serveraddr;
	thread mthread;
	queue<ActValue> mRecvQueue;
	queue<char> mSendQueue;
	playerNode* player;
	enemyNode* enemy;

	volatile bool isPlay;
	int buf;
	int checker;
public:
	Client();
	~Client();

	HRESULT init();
	void update();
	void setSendQueue(char data) { mSendQueue.emplace(data); }
	void setPlayerRef(playerNode* playerRef) { player = playerRef; }
	void setEnemyRef(enemyNode* enemyRef) { enemy = enemyRef; }
	void setPlayerBulletRef(enemyNode* enemyRef) { enemy = enemyRef; }
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

	int getCheckCount() { return checker;  }

	DWORD WINAPI RecvThread(LPVOID sockdata);
};