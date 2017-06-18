#pragma once
#include "animation.h"
enum RENDER_TYPE
{
	RENDER_NON,
	RENDER_BLEND,
	RENDER_STRETCH
};
class image
{
public:
	typedef struct tagImageInfo
	{
		HDC hMemDC;
		HBITMAP hB;
		HBITMAP hOldB;
		HDC hBlendDC;
		HBITMAP hBlendB;
		HBITMAP hBlendOldB;
		float x;
		float y;
		float w;
		float h;
		float frameX;
		float frameY;
		float maxFrameX;
		float maxFrameY;
		float frameW;
		float frameH;
		int alpha;
		RECT stretch;
		int offSetX;
		int offSetY;
		int loopW;
		int loopH;
		bool isLoop;
		tagImageInfo()
		{
			hMemDC = NULL;
			hB = NULL;
			hOldB = NULL;
			hBlendDC = NULL;
			hBlendB = NULL;
			hBlendOldB = NULL;
			x = 0;
			y = 0;
			w = 0;
			h = 0;
			frameX = 0;
			frameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameW = 0;
			frameH = 0;
			alpha = 0;
			stretch = RectMake(0, 0, 0, 0);
			offSetX = 0;
			offSetY = 0;
			loopW = 0;
			loopH = 0;
			isLoop = false;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;
private:
	LPIMAGE_INFO _imageInfo;
	TCHAR* _imageName;
	BOOL _trans;
	COLORREF _transColor;
	BLENDFUNCTION _blendFunction;
	RENDER_TYPE _type;
public:
	image();
	~image();
	HRESULT init(float w, float h);
	HRESULT init(const wchar_t* imageName, float w, float h, int frameX = 1, int frameY = 1, BOOL trans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	void release();
	void render(HDC hdc);
	void render(HDC hdc, float dx, float dy);
	void render(HDC hdc, float x, float y, float w, float h);
	void render(HDC hdc, float dx, float dy, float x, float y, float w, float h);
	void frameRender(HDC hdc, animation* frame);
	void frameRender(HDC hdc, float dx, float dy, animation* frame);
	void loop(HDC hdc);
	void loop(HDC hdc, float dx, float dy, float w, float h, int offSetX, int offSetY);
	void zoom(HDC hdc);

	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	inline void setType(RENDER_TYPE type) { _type = type; }
	inline float getX() { return _imageInfo->x; }
	inline float getY() { return _imageInfo->y; }
	inline void setX(float x) { _imageInfo->x = x; }
	inline void setY(float y) { _imageInfo->y = y; }
	inline void setXY(float x, float y)
	{
		_imageInfo->x = x;
		_imageInfo->y = y;
	}
	inline void setLoop(float loopW, float loopH)
	{
		_imageInfo->loopW = loopW;
		_imageInfo->loopH = loopH;
	}
	inline float getCenterX() { return _imageInfo->x + _imageInfo->frameW / 2; }
	inline float getCenterY() { return _imageInfo->y + _imageInfo->frameH / 2; }
	inline void setCenterXY(float x, float y)
	{
		_imageInfo->x = x + _imageInfo->frameW / 2;
		_imageInfo->y = y + _imageInfo->frameH / 2;
	}
	inline int getOffSetX() { return _imageInfo->offSetX; }
	inline int getOffSetY() { return _imageInfo->offSetY; }
	inline void setOffSetX(int x) { _imageInfo->offSetX = x; }
	inline void setOffSetY(int y) { _imageInfo->offSetY = y; }
	inline int getAlpha() { return _imageInfo->alpha; }
	inline void setAlpha(int alpha) { _imageInfo->alpha = alpha; }
	inline int getFrameX() { return _imageInfo->frameX; }
	inline int getFrameY() { return _imageInfo->frameY; }
	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }
	inline void setFrameX(int frameX) { _imageInfo->frameX = frameX; }
	inline void setFrameY(int frameY) { _imageInfo->frameY = frameY; }
	inline void setStretch(RECT rc) { _imageInfo->stretch = rc; }
	inline float getW() { return _imageInfo->w; }
	inline float getH() { return _imageInfo->h; }
	inline float getFrameW() { return _imageInfo->frameW; }
	inline float getFrameH() { return _imageInfo->frameH; }
};

