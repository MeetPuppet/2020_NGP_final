#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "ws2_32")

#pragma once
#include "ControlCode.h"
#include <winsock2.h>
#include "singletonBase.h"
#include <vector>
#include <queue>

class ObjectManager;

class NODE
{
public:
	int key;
	NODE* next;

	NODE()
	{
		key = 0;
		next = nullptr;
	}
	NODE(int key_value)
	{
		key = key_value;
		next = nullptr;
	}
	~NODE() {}
};

struct ServerClientSocket
{
	int id;
	SOCKET* listenSock;
	SOCKET socket;
	SOCKADDR_IN clientaddr;
	volatile bool isPlay;
	mutex localLock;

	char buf;
	thread recvThread;
	thread sendThread;
	//queue<ClientRequest> localRecvQueue;

	queue<ClientRequest>* RecvQueue;
	void LinkRecvQueue(queue<ClientRequest>* pRecvQueue) { RecvQueue = pRecvQueue; }

	queue<int> SendQueue;
	vector<char> log;

	ServerClientSocket();
	~ServerClientSocket();

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

	void SendActValue(ActValue actvalue);

	SOCKET getSocket() { return socket; };
	vector<char>* getLog() { return &log; }
	//int getQueueSize() { return localRecvQueue.size(); }

	void Activate(SOCKET* listen);
private:
	DWORD WINAPI RecvThread(LPVOID arg);
	DWORD WINAPI SendThread(LPVOID arg);
};

class Server : public singletonBase<Server>
{
private:

	WSADATA wsa;
	SOCKET listen_sock;
	SOCKADDR_IN serveraddr;
	volatile bool play;
	thread mThread;

	queue<ClientRequest> PublicRecvQueue;
	int totalQueueSize;

	ServerClientSocket Player1;
	ServerClientSocket Player2;
	ObjectManager* OM;

public:
	Server();
	~Server();

	HRESULT init();
	void update();

	ServerClientSocket* getPlayer1Sock() { return &Player1; }
	ServerClientSocket* getPlayer2Sock() { return &Player2; }
	int getQueueSize() { return PublicRecvQueue.size(); }

	bool isPlay() { return play; };
	void setPublicRecvQueue(const int& id,const char& data) { PublicRecvQueue.emplace(ClientRequest{ id, data }); }
	void LinkToObjectManager(ObjectManager* om) { OM = om; }

	vector<char>* getLog() { return Player1.getLog(); }

	//void ThreadActivate();
	//DWORD WINAPI PublicRecvThread(LPVOID arg);
};


