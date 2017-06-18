#pragma once
#include <vector>
class animation
{
public:
	typedef vector<POINT> vFrameList;
	typedef vector<int> vPlayList;
private:
	vFrameList _frameList;
	vPlayList _playList;
	int _maxFrameX;
	int _maxFrameY;
	int _frameW;
	int _frameH;
	BOOL _reverse;
	BOOL _loop;
	BOOL _play;
	float _frameUpdate;
	float _elapsedTime;
	int _frameNum;
	DWORD _curFrame;
public:
	animation();
	~animation();
	HRESULT init(float w, float h, int frameX, int frameY);
	void release();
	void setPlayFrame();
	void setFPS(int framePerSec = 1);
	void frameUpdate(float elapsedTime);
	void start();
	void stop();
	void pause();
	void resume();
	inline BOOL isPlay() { return _play; }
	inline POINT getFramePos() { return _frameList[_playList[_curFrame]]; }
	inline int getFrameW() { return _frameW; }
	inline int getFrameH() { return _frameH; }
	inline void setLoop(bool loop) { _loop = loop; }
	inline void setReverse(BOOL reverse) { _reverse = reverse; }
};

