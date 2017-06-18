#include "stdafx.h"
#include "keyManager.h"
keyManager::keyManager() {};
keyManager::~keyManager() {};
HRESULT keyManager::init()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		this->getKeyUp().set(i, false);
		this->getKeyDown().set(i, false);
	}
	return S_OK;
}
void keyManager::release()
{

}
bool keyManager::up(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		this->setKeyUp(key, true);
	}
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}
	return false;
}
bool keyManager::down(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else
	{
		this->setKeyDown(key, false);
	}
	return false;
}
bool keyManager::stay(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}
bool keyManager::toggle(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}