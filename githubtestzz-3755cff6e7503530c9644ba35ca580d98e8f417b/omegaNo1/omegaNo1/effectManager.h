#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>
class effect;
class effectManager : public singletonBase<effectManager>
{
private:
	typedef vector<effect*> arrEffects;
	typedef vector<effect*>::iterator iterEffects;
	typedef map<wstring, arrEffects> arrEffect;
	typedef map<wstring, arrEffects>::iterator iterEffect;
	typedef vector<map<wstring, arrEffects>> arrTotalEffect;
	typedef vector<map<wstring, arrEffects>>::iterator iterTotalEffect;
	arrTotalEffect _vTotalEffects;
public:
	HRESULT init();
	void release();
	void release(wstring effectName);
	void update();
	void render();
	void render(wstring effectName);
	void add(wstring effectName, wchar_t* imageName, int w, int h, int frameX, int frameY, float elapsedTime, int buffer, int fps = 1);
	void play(wstring effectName, float x, float y, bool center = FALSE);
	void stop(wstring effectName);
	effectManager();
	~effectManager();
};
