#include "stdafx.h"
#include "soundManager.h"


soundManager::soundManager()
{
}


soundManager::~soundManager()
{

}

HRESULT soundManager::init(void)
{
	//FMOD SOUND 엔진시스템 초기화
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	memset(_sound, 0, sizeof(Sound*) * TOTALSOUNDBUFFER);
	memset(_channel, 0, sizeof(Channel*) * TOTALSOUNDBUFFER);

	soundSet();
	return S_OK;
}

void soundManager::release(void)
{

}

void soundManager::update(void)	
{

}

void soundManager::soundSet()
{
	addSound("01.start", "sound/01start.mp3", false, false);
	addSound("02.shot", "sound/02shot.mp3", false, false);
	addSound("03.drone", "sound/03drone.mp3", false, false);
	addSound("04.connect", "sound/04connect.mp3", false, false);
	addSound("05.hit", "sound/05hit.mp3", false, false);
}

void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if ( loop )
	{
		if ( bgm )
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		if ( bgm )
		{
			_system->createStream(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
	}

	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}


void soundManager::play(string keyName, float volume) //0.0 ~ 1.0f
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for ( iter; iter != _mTotalSounds.end(); ++iter, count++ )
	{
		if ( keyName == iter->first )
		{
			_system->playSound(FMOD_CHANNEL_FREE, _sound[count], false, &_channel[count]);

			_channel[count]->setVolume(volume);
			break;
		}
	}

}

void soundManager::stop(string keyName)	 
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for ( iter; iter != _mTotalSounds.end(); ++iter, count++ )
	{
		if ( keyName == iter->first )
		{
			_channel[count]->stop();
			break;
		}
	}

}

void soundManager::pause(string keyName) 
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for ( iter; iter != _mTotalSounds.end(); ++iter, count++ )
	{
		if ( keyName == iter->first )
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for ( iter; iter != _mTotalSounds.end(); ++iter, count++ )
	{
		if ( keyName == iter->first )
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}


//사운드 이벤트 처리용
bool soundManager::isPlaySound(string keyName) 
{
	bool isPlay;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for ( iter; iter != _mTotalSounds.end(); ++iter, count++ )
	{
		if ( keyName == iter->first )
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for ( iter; iter != _mTotalSounds.end(); ++iter, count++ )
	{
		if ( keyName == iter->first )
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}
