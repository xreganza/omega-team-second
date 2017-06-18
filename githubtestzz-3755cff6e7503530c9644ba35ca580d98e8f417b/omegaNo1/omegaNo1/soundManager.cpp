#include "stdafx.h"
#include "soundManager.h"
soundManager::soundManager() : _system(NULL), _sound(NULL), _channel(NULL) {};
soundManager::~soundManager() {};
HRESULT soundManager::init()
{
	System_Create(&_system);
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);
	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];
	memset(_sound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	return S_OK;
}
void soundManager::release()
{
	if (_channel != NULL || _sound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}
			if (_sound != NULL)
			{
				if (_sound != NULL) _sound[i]->release();
			}
		}
	}
	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}
void soundManager::addSound(wstring keyName, wstring soundName, bool bgm, bool loop)
{
	if (loop)
	{
		if (bgm)
		{
			_system->createStream((const char*)soundName.c_str(), FMOD_LOOP_NORMAL | FMOD_UNICODE, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound((const char*)soundName.c_str(), FMOD_DEFAULT | FMOD_UNICODE, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		if (bgm)
		{
			_system->createStream((const char*)soundName.c_str(), FMOD_DEFAULT | FMOD_UNICODE, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound((const char*)soundName.c_str(), FMOD_DEFAULT | FMOD_UNICODE, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}
void soundManager::play(wstring keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);
			_channel[count]->setVolume(volume);
			break;
		}
	}
}
void soundManager::stop(wstring keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}
void soundManager::pause(wstring keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}
void soundManager::resume(wstring keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}
bool soundManager::isPlaySound(wstring keyName)
{
	bool isPlay;
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}
	return isPlay;
}
bool soundManager::isPauseSound(wstring keyName)
{
	bool isPause;
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}
	return isPause;
}
void soundManager::update(void)
{
	_system->update();
}