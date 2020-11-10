#include "stdafx.h"
#include "timer.h"
#include <mmsystem.h>	//timeGetTime() 함수를 쓸수있게해준다

#pragma comment(lib, "winmm.lib")

timer::timer()
{
}


timer::~timer()
{
}

HRESULT timer::init(void)
{
	if ( QueryPerformanceFrequency((LARGE_INTEGER*) &_periodFrequency))
	{
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*) &_lastTime);

		_timeScale = 1.0f / _periodFrequency;
	}
	else
	{
		_isHardware = false;

		_lastTime = timeGetTime();	//강제로 1000분의 1초로 맞춰준다
		_timeScale = 0.001f;		//Epsilon == 실수의 가장 작은단위
	}

	_frameRate = 0;
	_FPSframeCount = 0;
	_FPSTimeElapsed = 0;
	_worldTime = 0;


	return S_OK;
}

void timer::tick(float lockFPS)
{
	if ( _isHardware )
	{
		QueryPerformanceCounter((LARGE_INTEGER*) &_curTime);
	}
	else
	{
		_curTime = timeGetTime();
	}

	//고정 틱카운트 구한다
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	//프레임 스키핑
	if ( lockFPS > 0.0f )
	{
		while ( _timeElapsed < (1.0f / lockFPS) )
		{
			if ( _isHardware ) QueryPerformanceCounter((LARGE_INTEGER*) &_curTime);
			else _curTime = timeGetTime();

			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}
	
	_lastTime = _curTime;
	_FPSframeCount++;
	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;

	if ( _FPSTimeElapsed > 1.0f )
	{
		_frameRate = _FPSframeCount;
		_FPSframeCount = 0;
		_FPSTimeElapsed = 0.0f;
	}


}

unsigned long timer::getFrameRate(char* str) const
{
	if ( str != NULL )
	{
		wsprintf(str, "FPS : %d", _frameRate);
	}

	return _frameRate;
}