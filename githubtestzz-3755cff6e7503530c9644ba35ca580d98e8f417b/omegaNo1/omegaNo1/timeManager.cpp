#include "stdafx.h"
#include "timeManager.h"
timeManager::timeManager() : _timer(NULL) {};
timeManager::~timeManager() {};
HRESULT timeManager::init()
{
	_timer = new timer;
	_timer->init();

	return S_OK;
}
void timeManager::release()
{
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
		_timer = NULL;
	}
}
void timeManager::update(float lock)
{
	if (_timer != NULL)
	{
		_timer->tick(lock);
	}
}
void timeManager::render(HDC hdc)
{
	TCHAR str[256];
	wstring frameRate;
	SetBkMode(hdc, TRANSPARENT);
#ifdef _DEBUG
	{
		wsprintf(str, L"framePerSec(FPS) : %d", _timer->getFrameRate());
		TextOutW(hdc, 0, 0, str, wcslen(str));
		swprintf_s(str, L"worldTime : %f", _timer->getWorldTime());
		TextOutW(hdc, 0, 20, str, wcslen(str));
		swprintf_s(str, L"elaspedTime : %f", _timer->getElapsedTime());
		TextOutW(hdc, 0, 40, str, wcslen(str));
	}
#else
	{
		wsprintf(str, L"framePerSec(FPS) : %d", _timer->getFrameRate());
		TextOutW(hdc, 0, 0, str, wcslen(str));
		swprintf_s(str, L"worldTime : %f", _timer->getWorldTime());
		TextOutW(hdc, 0, 20, str, wcslen(str));
		swprintf_s(str, L"elaspedTime : %f", _timer->getElapsedTime());
		TextOutW(hdc, 0, 40, str, wcslen(str));
	}
#endif
}