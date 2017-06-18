#include "stdafx.h"
#include "imageManager.h"
imageManager::imageManager() {};
imageManager::~imageManager() {};
HRESULT imageManager::init()
{
	return S_OK;
}
void imageManager::release()
{

}
image* imageManager::add(wstring key, float w, float h)
{
	image* img = find(key);
	if (img) return img;
	img = new image;
	if (FAILED(img->init(w, h)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(make_pair(key, img));
	return img;
}
image* imageManager::add(wstring key, const wchar_t* imageName, float w, float h, int frameX, int frameY, bool trans, COLORREF transColor)
{
	image* img = find(key);
	if (img) return img;
	img = new image;
	if (FAILED(img->init(imageName, w, h, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(make_pair(key, img));
	return img;
}
image* imageManager::find(wstring key)
{
	_miImageList = _mImageList.find(key);
	if (_miImageList != _mImageList.end())
	{
		return _miImageList->second;
	}
	return NULL;
}