#pragma once
#include "singletonBase.h"
#include <bitset>
#define KEYMAX 256
class keyManager : public singletonBase<keyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;
public:
	HRESULT init();
	void release();
	bool up(int key);
	bool down(int key);
	bool stay(int key);
	bool toggle(int key);

	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }

	keyManager();
	~keyManager();
};

