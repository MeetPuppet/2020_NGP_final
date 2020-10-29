#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             

#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "utils.h"
#include "collision.h"
#include "imageManager.h"
#include "timeManager.h"
#include "soundManager.h"
#include "sceneManager.h"

using namespace std;

/*
윈도우 관련 디파인
*/
#define WINNAME		(LPTSTR)(TEXT("Window Name"))
#define WINSTARTX	50
#define WINSTARTY	50
#define WINSIZEX	1000
#define WINSIZEY	1000
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

/*
싱글톤 매니저 관련 디파인
*/
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()

/*
메모리해제 관련 디파인
*/
#define SAFE_DELETE(p) {if(p) {delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)=NULL;}}

/*
extern 변수
*/
extern HINSTANCE _hInstance;	
extern HWND	_hWnd;			
extern POINT _ptMouse;
extern BOOL _leftMouseButton;


struct Point {
	float x;
	float y;

	Point() {
		x = 0;
		y = 0;
	}
	Point(int x, int y) : x(x), y(y) {
		;
	}
	Point(const Point& other) {
		x = other.x;
		y = other.y;
	}
	Point(POINT p) {
		x = p.x;
		y = p.y;
	}

	//입력용 제발 숫자만
	template<typename T>
	Point operator()(T a, T b) {
		x = a;
		y = b;
		return *this;
	}
};

