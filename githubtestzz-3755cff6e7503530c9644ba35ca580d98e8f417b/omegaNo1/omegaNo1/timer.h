#pragma once
class timer
{
private:
	bool _hardware;
	float _timeScale;
	float _elapsedTime;
	float _worldTime;
	__int64 _curTime;
	__int64 _lastTime;
	__int64 _periodFrequency;
	unsigned long _frameRate;
	unsigned long _FPSFrameCount;
	float _elapsedFPSTime;
	bool _stop;
public:
	timer();
	~timer();
	HRESULT init();
	void tick(float lockFPS = 0);
	unsigned long getFrameRate(wchar_t* str = NULL) const;
	inline float getElapsedTime() const { return _elapsedTime; }
	inline float getWorldTime() const { return _worldTime; }
	inline bool getStop() { return _stop; }
	inline void setStop(bool stop) { _stop = stop; }
};

