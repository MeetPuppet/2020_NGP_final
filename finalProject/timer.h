#pragma once
class timer
{
private:
	bool _isHardware;	//고성능 하드웨어 지원여부
	float _timeScale;	//FPS 빈도
	float _timeElapsed;	//tick Count (밀리세컨)

	__int64 _curTime;
	__int64 _lastTime;
	__int64 _periodFrequency;

	unsigned long _frameRate;
	unsigned long _FPSframeCount;

	float _FPSTimeElapsed;
	float _worldTime;

public:
	HRESULT init(void);
	void tick(float lockFPS = 0.0f);
	unsigned long getFrameRate(char* str = NULL) const;

	inline float getElapsedTime(void) const { return _timeElapsed; }
	inline float getWorldTime(void) const { return _worldTime; }


	timer();
	~timer();
};

