#pragma once
#include "gameNode.h"
class battle;
class mainGame : public gameNode
{
private:
	RECT _rc;
	image* _im2;
	int _loopX;
	animation* _ani;
	battle* _battle;
public:
	mainGame();
	~mainGame();
	HRESULT init();
	void release();
	void update();
	void render();
	
	void test();
	void test2();
};

