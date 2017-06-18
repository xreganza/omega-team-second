#pragma once
#include "image.h"
static image* _backBuffer = IM->add(L"backBuffer", WINSIZEX, WINSIZEY);
class gameNode
{
private:
	HDC _hdc;
	bool _initManager;
public:
	gameNode();
	virtual ~gameNode();
	virtual HRESULT init();
	virtual HRESULT init(bool init);
	virtual void release();
	virtual void update();
	virtual void render();
	inline image* getBackBuffer() { return _backBuffer; }
	inline HDC getMemDC() { return _backBuffer->getMemDC(); }
	inline HDC getHDC() { return _hdc; }
	LRESULT mainProc(HWND, UINT, WPARAM, LPARAM);
};

