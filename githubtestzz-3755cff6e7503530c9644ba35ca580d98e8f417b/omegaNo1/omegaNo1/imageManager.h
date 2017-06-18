#pragma once
#include "singletonBase.h"
#include "image.h"
#include <map>
class imageManager : public singletonBase<imageManager>
{
private:
	map<wstring, image*> _mImageList;
	map<wstring, image*>::iterator _miImageList;
public:
	imageManager();
	~imageManager();
	HRESULT init();
	void release();
	image* add(wstring key, float w, float h);
	image* add(wstring key, const wchar_t* imageName, float w, float h, int frameX = 1, int frameY = 1, bool trans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	image* find(wstring key);
};

