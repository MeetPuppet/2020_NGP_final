#pragma once
#include "singletonBase.h"
#include "stdafx.h"//�Ŵ����� ���⿡ �� ���������� �ʿ���
#include "ControlCode.h"
#include <winsock2.h>
#include <queue>

#pragma comment(lib, "ws2_32")

#pragma once
class Client : public singletonBase<Client>
{
private:
	WSADATA wsa;
	SOCKET sock;
	SOCKADDR_IN serveraddr;
	queue<ActValue> mRecvQueue;
	queue<char> mSendQueue;

public:
	Client();
	~Client();

	HRESULT init();
	void update();
	void setSendQueue(char data) { mSendQueue.emplace(data); }
	//void getRecvQueue(ActValue data) { mRecvQueue.emplace(data); }
};