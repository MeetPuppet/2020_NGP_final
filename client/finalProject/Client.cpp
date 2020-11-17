#include "Client.h"
#include "playerNode.h"
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
}

void Client::update()
{
	while (mSendQueue.size() != 0)
	{
		char send_data = mSendQueue.front();
		send(sock, (char *)&send_data, sizeof(char), 0);
		mSendQueue.pop();
	}
}
