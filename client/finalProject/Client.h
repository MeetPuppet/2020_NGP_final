#include "singletonBase.h"
#include "ControlCode.h"
#include <winsock2.h>
#include <queue>

#pragma comment(lib, "ws2_32")

#pragma once
class Client : public singletonBase <Client>
{
private:
	WSADATA wsa;
	SOCKET sock;
	SOCKADDR_IN serveraddr;
	queue<ActValue> RecvQueue;
	queue<char> SendQueue;

public:
	Client();
	~Client();

	HRESULT init();
	void update();
};

