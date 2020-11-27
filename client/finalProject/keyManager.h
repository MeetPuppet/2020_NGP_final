#pragma once
#include "singletonBase.h"
#include <bitset>
#include <queue>

using namespace std;

struct KeyPair
{
	char key;
	bool isDown;

	bool operator==(KeyPair other) {
		if (key == 0 && isDown == 0)
			return false;
		return true;
	}
};
#define KEYMAX 256

class keyManager : public singletonBase<keyManager>
{
private:
	bool queueMode;

	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	HRESULT init();
	void release();

	bool isOnceKeyDown(int key);
	HRESULT init(bool isQueue);
	bool isOnceKeyUp(int key);
	bool isStayKeyDown(int key);
	bool isToggleKey(int key);

	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }

	keyManager();
	~keyManager();
};

