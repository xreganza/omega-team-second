#pragma once
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <memory.h>
#include <tchar.h>

using namespace std;
#include "randomFunction.h"
#include "RectMakeFunction.h"
#include "mathFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "timeManager.h"
#include "soundManager.h"
#include "effectManager.h"
#include "txtData.h"

#define RND randomFunction::getSingleton()
#define KEYM keyManager::getSingleton()
#define IM imageManager::getSingleton()
#define TIMEM timeManager::getSingleton()
#define SOUNDM soundManager::getSingleton()
#define EFFECTM effectManager::getSingleton()
#define TXTDATA txtData::getSingleton()

#define WINNAME (LPTSTR)L"z"
#define WINSTARTX 200
#define WINSTARTY 100
#define WINSIZEX 1500
#define WINSIZEY 800

#define SAFE_DELETE(p) {if(p){delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p){(p)->release(); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p){delete[] (p); (p) = NULL;}}

extern HWND _hWnd;
extern HINSTANCE _hInstance;
extern POINT _ptMouse;