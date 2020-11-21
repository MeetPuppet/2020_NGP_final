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

struct ServerClientSocket
{
	int id;
	SOCKET* listenSock;
	SOCKET socket;
	SOCKADDR_IN clientaddr;
	volatile bool isPlay;
	mutex localLock;

	char buf;
	thread mThread;
	queue<ClientRequest> localRecvQueue;

	//queue<ActValue> SendQueue;
	vector<char> SendLog;
	vector<char> RecvLog;

	ServerClientSocket();
	~ServerClientSocket();

	void Activate(SOCKET* listen);
	DWORD WINAPI RecvThread(LPVOID arg);
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
	vector<char>* getSendLog() { return &SendLog; }
	vector<char>* getRecvLog() { return &RecvLog; }
	
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

	bool isPlay() { return play; };
	void setPublicRecvQueue(const int& id,const char& data) { PublicRecvQueue.emplace(ClientRequest{ id, data }); }
	void LinkToObjectManager(ObjectManager* om) { OM = om; }

	vector<char>* getSendLog() { return Player1.getSendLog(); }
	vector<char>* getRecvLog() { return Player1.getRecvLog(); }

	void ThreadActivate();
	DWORD WINAPI PublicRecvThread(LPVOID arg);
};


