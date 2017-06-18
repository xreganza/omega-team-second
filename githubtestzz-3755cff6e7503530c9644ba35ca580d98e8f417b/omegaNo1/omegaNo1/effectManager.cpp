#include "stdafx.h"
#include "effectManager.h"
#include "effect.h"
effectManager::effectManager() {};
effectManager::~effectManager() {};
HRESULT effectManager::init()
{
	return S_OK;
}
void effectManager::release()
{
	iterTotalEffect vIter;
	iterEffect mIter;
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		mIter = vIter->begin();
		for (; mIter != vIter->end();)
		{
			if (mIter->second.size() != 0)
			{
				iterEffects vArrIter = mIter->second.begin();
				for (; vArrIter != mIter->second.end();)
				{
					if ((*vArrIter))
					{
						(*vArrIter)->release();
						delete *vArrIter;
						vArrIter = mIter->second.erase(vArrIter);
					}
					else
					{
						++vArrIter;
					}
				}
			}
			else
			{
				++mIter;
			}
		}
	}
}
void effectManager::release(wstring effectName)
{
	iterTotalEffect vIter;
	iterEffect mIter;
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		mIter = vIter->begin();
		for (; mIter != vIter->end();)
		{
			if (!(mIter->first == effectName)) break;
			if (mIter->second.size() != 0)
			{
				iterEffects vArrIter = mIter->second.begin();
				for (; vArrIter != mIter->second.end();)
				{
					if ((*vArrIter))
					{
						(*vArrIter)->release();
						delete *vArrIter;
						vArrIter = mIter->second.erase(vArrIter);
					}
					else
					{
						++vArrIter;
					}
				}
			}
			else
			{
				++mIter;
			}
		}
	}
}
void effectManager::update()
{
	iterTotalEffect vIter;
	iterEffect mIter;
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->update();
			}
		}
	}
}
void effectManager::render()
{
	iterTotalEffect vIter;
	iterEffect mIter;
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->render();
			}
		}
	}
}
void effectManager::render(wstring effectName)
{
	iterTotalEffect vIter;
	iterEffect mIter;
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (!(mIter->first == effectName)) break;
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->render();
			}
		}
	}
}
void effectManager::add(wstring effectName, wchar_t* imageName, int w, int h, int frameX, int frameY, float elapsedTime, int buffer, int fps)
{
	image* img;
	arrEffects vEffectBuffer;
	arrEffect mArrEffect;
	if (IM->find(imageName))
	{
		img = IM->find(imageName);
	}
	else
	{
		img = IM->add(imageName, imageName, w, h);
	}
	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, frameX, frameY, elapsedTime, fps);
	}
	mArrEffect.insert(pair<wstring, arrEffects>(effectName, vEffectBuffer));
	_vTotalEffects.push_back(mArrEffect);
}
void effectManager::play(wstring effectName, float x, float y, bool center)
{
	iterTotalEffect vIter;
	iterEffect mIter;
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (!(mIter->first == effectName)) break;

			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->getIsRunning()) continue;
				(*vArrIter)->start(x, y, center);
				return;
			}
		}
	}
}
void effectManager::stop(wstring effectName)
{
	iterTotalEffect vIter;
	iterEffect mIter;
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (!(mIter->first == effectName)) break;
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if (!(*vArrIter)->getIsRunning()) continue;
				(*vArrIter)->stop();
				return;
			}
		}
	}
}