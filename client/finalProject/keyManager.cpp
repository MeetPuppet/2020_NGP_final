#include "stdafx.h"
#include "keyManager.h"


keyManager::keyManager()
{
}


keyManager::~keyManager()
{

}

HRESULT keyManager::init()
{
	queueMode = false;
	for (int i = 0; i < KEYMAX; i++)
	{
		this->getKeyUp().set(i, false);
		this->getKeyUp().set(i, false);
	}

	return S_OK;
}
HRESULT keyManager::init(bool isQueue = false)
{
	queueMode = isQueue;
	for (int i = 0; i < KEYMAX; i++)
	{
		this->getKeyUp().set(i, false);
		this->getKeyUp().set(i, false);
	}
	//if (queueMode == false) {
	//}

	return S_OK;
}

void keyManager::release()
{

}


bool keyManager::isOnceKeyDown(int key)
{
	//GetKeyState			== 동기
	//GetASyncKeyState		== 비동기
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			if (queueMode) {
				qKey.emplace(KeyPair{ (char)key, true });
			}
			this->setKeyDown(key, true);
			return true;
		}
	}
	else this->setKeyDown(key, false);


	return false;
}

bool keyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) this->setKeyUp(key, true);
	else
	{
		if (this->getKeyUp()[key])
		{
			if (queueMode) {
				qKey.emplace(KeyPair{ (char)key, false });
			}
			this->setKeyUp(key, false);
			return true;
		}
	}

	return false;
}

bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;

	return false;
}

bool keyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;

	return false;
}

KeyPair keyManager::autoOutKey()
{
	KeyPair key = qKey.front();
	qKey.pop();
	return key;
}

int keyManager::autoOutSize()
{
	return qKey.size();
}
