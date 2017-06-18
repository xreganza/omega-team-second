#pragma once
#include "gameNode.h"
class animation;
class effect : public gameNode
{
protected:
	float _x;
	float _y;
	image* _effectImage;
	animation* _effectAnimation;
	BOOL _isRunning;
	float _elapsedTime;
public:
	effect();
	~effect();
	virtual HRESULT init(image* effectImage, int frameX, int frameY, float elapsedTime, int fps = 1);
	virtual void release();
	virtual void update();
	virtual void render();
	void start(float x, float y, bool center = FALSE);
	void stop();
	BOOL getIsRunning() { return _isRunning; }
};

