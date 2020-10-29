#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{

}

//friend 선언 시, 함수 혹은 클래스는 private까지 그냥 접근이 가능케 됨.
//굉장히 자주 쓰이게 되는데 객체간의 통신을 원할하게 하는게 편한 경우 아니면
//남발하면 안됨

DWORD CALLBACK loadingThread(LPVOID prc)
{
	//준비할 씬을 미리 초기화 시켜둔다
	sceneManager::_readyScene->init();

	//준비된 씬을 현재씬으로 교체한다
	sceneManager::_currentScene = sceneManager::_readyScene;

	//로딩에 쓰인 씬을 해제한다
	sceneManager::_loadingScene->release();
	sceneManager::_loadingScene = NULL;
	sceneManager::_readyScene = NULL;

	return 0;
}

gameNode* sceneManager::_currentScene = NULL;
gameNode* sceneManager::_loadingScene = NULL;
gameNode* sceneManager::_readyScene = NULL;

HRESULT sceneManager::init(void)
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;
	
	return S_OK;
}

void sceneManager::release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for ( ; miSceneList != _mSceneList.end(); )
	{
		if ( miSceneList->second != NULL )
		{
			if ( miSceneList->second == _currentScene ) miSceneList->second->release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void sceneManager::update(void)	
{
	if ( _currentScene ) _currentScene->update();
}

void sceneManager::render(void)	
{
	if ( _currentScene ) _currentScene->render();
}


//씬 추가 관련 함수
gameNode* sceneManager::addScene(string sceneName, gameNode* scene)				 
{
	//씬이 없다면 널값 반환
	if ( !scene ) return NULL;

	//씬이름 과 해당 씬을 맵에 넣는다
	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

gameNode* sceneManager::addLoadingScene(string loadingSceneName, gameNode* scene)
{
	//씬이 없다면 널값 반환
	if ( !scene ) return NULL;

	//씬이름 과 해당 씬을 맵에 넣는다
	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}


//씬 변경
HRESULT sceneManager::changeScene(string sceneName)							
{
	//이터레이터에 찾고자하는 씬의 키값을 넣고
	mapSceneIter find = _mSceneList.find(sceneName);

	//못찾았다면 실패했다고 알린다
	if ( find == _mSceneList.end() ) return E_FAIL;

	//만약에 찾은 씬이 현재 씬과 동일하면 바꾸지 않는다
	if ( find->second == _currentScene ) return S_OK;

	//만약 바꾸려닌 씬이 '성공적'으로 바뀌었다면 init함수를 호출한다
	if ( SUCCEEDED(find->second->init()) )
	{
		//현재 씬(다른씬이 있다면) 해당씬을 날려주고
		if ( _currentScene ) _currentScene->release();
		//바꾸려는 씬으로 씬을 바꿔준다
		_currentScene = find->second;

		//이 부분은 나중에 여러분 입맛에 따라 바꿀 필요가 있다.
		//위에 구조는 만약에 스테이지1에서 어떤 DB 자료를 저장하고
		//씬을 바꾸려고 하면 릴리즈가 먼저 호출이 되기때문에
		//정보가 넘어오지 않는 구조이다. 

		return S_OK;
	}

	return E_FAIL;
}

//나중에 잘 개조해봐밤 가랏 신우 너로 정했다
HRESULT sceneManager::changeScene(string sceneName, string loadingSceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	if ( find == _mSceneList.end() ) return E_FAIL;
	if ( find->second == _currentScene ) return S_OK;

	//로딩하려는 씬을 찾는다
	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	if ( find == _mLoadingSceneList.end() ) return changeScene(loadingSceneName);

	if ( SUCCEEDED(find->second->init()) )
	{
		if ( _currentScene ) _currentScene->release();

		_loadingScene = findLoading->second;
		_readyScene = find->second;
		CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &_loadingThreadID));
	}

	return E_FAIL;
}


