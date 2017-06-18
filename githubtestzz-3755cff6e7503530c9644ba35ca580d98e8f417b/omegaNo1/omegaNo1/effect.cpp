#include "stdafx.h"
#include "effect.h"
#include "animation.h"
effect::effect() : _effectImage(NULL), _effectAnimation(NULL), _isRunning(false), _x(0), _y(0) {};
effect::~effect() {};
HRESULT effect::init(image* effectImage, int frameX, int frameY, float elapsedTime, int fps)
{
	if (!effectImage) return E_FAIL;
	_isRunning = false;
	_effectImage = effectImage;
	_elapsedTime = elapsedTime;
	if (!_effectAnimation) _effectAnimation = new animation;
	_effectAnimation->init(_effectImage->getW(), _effectImage->getH(), frameX, frameY);
	_effectAnimation->setFPS(fps);
	_effectAnimation->setLoop(false);
	_effectAnimation->stop();	

	return S_OK;
}
void effect::release()
{
	_effectImage = NULL;
	SAFE_DELETE(_effectAnimation);
}
void effect::update()
{
	if (!_isRunning) return;
	_effectAnimation->frameUpdate(_elapsedTime);
	if (!_effectAnimation->isPlay()) stop();
}
void effect::render()
{
	if (!_isRunning) return;
	_effectImage->frameRender(getMemDC(), _x, _y, _effectAnimation);
}
void effect::start(float x, float y, bool center)
{
	if (!_effectImage || !_effectAnimation) return;
	if (center)
	{
		_x = x - _effectAnimation->getFrameW() / 2;
		_y = y - _effectAnimation->getFrameH() / 2;
	}
	else
	{
		_x = x;
		_y = y;
	}
	_isRunning = true;
	_effectAnimation->start();
}
void effect::stop()
{
	_isRunning = false;
}