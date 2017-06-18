#include "stdafx.h"
#include "gameNode.h"
gameNode::gameNode() {};
gameNode::~gameNode() {};
HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_initManager = false;

	return S_OK;
}
HRESULT gameNode::init(bool init)
{
	_hdc = GetDC(_hWnd);
	_initManager = init;
	if (_initManager)
	{
		KEYM->init();
		IM->init();
		TIMEM->init();
		SOUNDM->init();
		TXTDATA->init();
	}

	return S_OK;
}
void gameNode::release()
{
	if (_initManager)
	{
		KEYM->releaseSingleton();
		IM->releaseSingleton();
		TIMEM->releaseSingleton();
		SOUNDM->releaseSingleton();
		TXTDATA->releaseSingleton();
	}
	ReleaseDC(_hWnd, _hdc);
}
void gameNode::update()
{
	
}
void gameNode::render()
{
	
}
LRESULT gameNode::mainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
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
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}