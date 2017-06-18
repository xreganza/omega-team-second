#include "stdafx.h"
#include "timer.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
timer::timer() {};
timer::~timer() {};
HRESULT timer::init()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		_hardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
		_timeScale = 1.0 / _periodFrequency;
	}
	else
	{
		_hardware = false;
		_lastTime = timeGetTime();
		_timeScale = 0.0001;
	}
	_frameRate = 0;
	_FPSFrameCount = 0;
	_elapsedFPSTime = 0;
	_worldTime = 0;
	_stop = false;

	return S_OK;
}
void timer::tick(float lockFPS)
{
	if (_hardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		_curTime = timeGetTime();
	}
	_elapsedTime = (_curTime - _lastTime) * _timeScale;
	if (lockFPS > 0.0)
	{
		while (_elapsedTime< (1.0 / lockFPS))
		{
			if (_hardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else _curTime = timeGetTime();

			_elapsedTime = (_curTime - _lastTime) * _timeScale;
		}
	}
	_lastTime = _curTime;
	_FPSFrameCount++;
	_elapsedFPSTime += _elapsedTime;
	if (!_stop) _worldTime += _elapsedTime;
	if (_elapsedFPSTime> 1.0)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_elapsedFPSTime = 0.0;
	}
}
unsigned long timer::getFrameRate(wchar_t* str) const
{
	if (str != NULL)
	{
		wsprintf(str, L"FPS : %d", _frameRate);
	}

	return _frameRate;
}