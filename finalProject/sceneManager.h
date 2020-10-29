#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

//gameNode 클래스는 전방선언으로!
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	static gameNode* _currentScene;	//현재 씬
	static gameNode* _loadingScene;	//로딩 씬
	static gameNode* _readyScene;	//대기 씬(로딩이 끝난후 바뀔 씬이라던지)

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadingThreadID;
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//씬 추가 관련 함수
	gameNode* addScene(string sceneName, gameNode* scene);
	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	//씬 변경
	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName, string loadingSceneName);

	friend DWORD CALLBACK loadingThread(LPVOID prc);



	sceneManager();
	~sceneManager();
};

