#include "stdafx.h"
#include "animation.h"
animation::animation() : _frameW(0), _frameH(0), _reverse(FALSE), _loop(FALSE), _frameUpdate(0), _elapsedTime(0), _frameNum(0), _curFrame(0), _play(FALSE) {};
animation::~animation() {};
HRESULT animation::init(float w, float h, int frameX, int frameY)
{
	_frameW = (int)w / frameX;
	_frameH = (int)h / frameY;
	int frameNumW = w / _frameW;
	int frameNumH = h / _frameH;
	_frameNum = frameNumW * frameNumH;
	for (int i = 0; i < frameNumH; i++)
	{
		for (int j = 0; j < frameNumW; j++)
		{
			POINT framePos;
			framePos.x = j * _frameW;
			framePos.y = i * _frameH;
			_frameList.push_back(framePos);
		}
	}
	_play = TRUE;
	_loop = TRUE;
	_reverse = FALSE;
	_frameUpdate = 1.0;
	setPlayFrame();

	return S_OK;
}
void animation::release()
{

}
void animation::setPlayFrame()
{
	_playList.clear();
	if (_reverse)
	{
		if (_loop)
		{
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			for (int i = _frameNum - 1; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			for (int i = _frameNum - 1; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		if (_loop)
		{
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
		}
	}
}
void animation::setFPS(int framePerSec)
{
	_frameUpdate = 1.0 / framePerSec;
}
void animation::frameUpdate(float elapsedTime)
{
	if (_play)
	{
		_elapsedTime += elapsedTime;
		if (_elapsedTime >= _frameUpdate)
		{
			_elapsedTime -= _frameUpdate;
			_curFrame += 1;
			if (_curFrame == _playList.size())
			{
				if (_loop) _curFrame = 0;
				else
				{
					_curFrame -= 1;
					_play = FALSE;
				}
			}
		}
	}
}
void animation::start()
{	 
	_play = TRUE;
	_curFrame = 0;
}	 
void animation::stop()
{
	_play = FALSE;
	_curFrame = 0;
}
void animation::pause()
{
	_play = FALSE;
}
void animation::resume()
{
	_play = TRUE;
}