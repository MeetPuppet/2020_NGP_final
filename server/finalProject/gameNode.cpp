#include "stdafx.h"
#include "gameNode.h"

gameNode::gameNode()
{
}


gameNode::~gameNode()
{

}

//HRESULT == MS디버깅 
//S_OK
//E_FAIL
//SUCCEDED
HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if ( _managerInit )
	{
		//타이머 셋팅 == 0.01
		//SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		SOUNDMANAGER->init();
		SCENEMANAGER->init();
		SERVER->init();
	}


	return S_OK;
}

void gameNode::release()
{
	if ( _managerInit )
	{
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->releaseSingleton();
		TIMEMANAGER->releaseSingleton();
		SOUNDMANAGER->releaseSingleton();
		SCENEMANAGER->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
	
}
		
void gameNode::update()	
{
	InvalidateRect(_hWnd, NULL, false);
	if (_managerInit)
	{
		SERVER->update();
	}
	
}
	
void gameNode::render()
{

}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	ActValue act;

	switch (iMessage)
	{
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>LOWORD(lParam);
			_ptMouse.y = static_cast<float>HIWORD(lParam);

		break;
		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
					PostMessage(hWnd, WM_DESTROY, 0, 0);
				break;
			}
		break;

		case WM_DESTROY:
			act.infoType = UNCONNECT;
			SERVER->getPlayer1Sock()->SendActValue(act);
			SERVER->getPlayer2Sock()->SendActValue(act);
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
