#include "stdafx.h"
#include "mainGame.h"
mainGame::mainGame() {};
mainGame::~mainGame() {};

HRESULT mainGame::init()
{
	gameNode::init(true);



	return S_OK;
}
void mainGame::release()
{
	gameNode::release();
}
void mainGame::update()
{
	gameNode::update();
	// don`t write korean T.T
	

	//sgpnsdgpgsdngs
}
void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);



	TIMEM->render(getMemDC());
	this->getBackBuffer()->render(getHDC());
}
