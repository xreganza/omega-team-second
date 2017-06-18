#include "stdafx.h"
#include "mainGame.h"
HWND _hWnd;
HINSTANCE _hInstance;
POINT _ptMouse;
mainGame _mg;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(float x, float y, float w, float h);
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;
	_hInstance = hInstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndClass);

	_hWnd = CreateWindow(WINNAME, WINNAME, WS_OVERLAPPEDWINDOW, WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY, NULL, (HMENU)NULL, hInstance, NULL);
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
	ShowWindow(_hWnd, cmdShow);

	if (FAILED(_mg.init()))
	{
		return 0;
	}

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEM->update(60.0);
			_mg.update();
			_mg.render();
		}
	}

	_mg.release();

	return message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg.mainProc(hWnd, iMessage, wParam, lParam);
}
void setWindowSize(float x, float y, float w, float h)
{
	RECT winRect;
	winRect.left = x;
	winRect.top = y;
	winRect.right = x + w;
	winRect.bottom = y + h;

	AdjustWindowRect(&winRect, WS_CAPTION | WS_SYSMENU, false);
	SetWindowPos(_hWnd, NULL, x, y, winRect.right - winRect.left, winRect.bottom - winRect.top, SWP_NOZORDER | SWP_NOMOVE);
}