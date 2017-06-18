#include "stdafx.h"
#include "image.h"
#pragma comment(lib, "msimg32.lib")
image::image() : _imageInfo(NULL), _imageName(NULL), _trans(false), _transColor(RGB(0, 0, 0)), _type(RENDER_NON) {};
image::~image() {};
HRESULT image::init(float w, float h)
{
	if (_imageInfo != NULL) release();
	HDC hdc = GetDC(_hWnd);
	_imageInfo = new IMAGE_INFO;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hB = (HBITMAP)CreateCompatibleBitmap(hdc, w, h);
	_imageInfo->hOldB = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hB);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->w = w;
	_imageInfo->h = h;
	_imageInfo->frameX = 0;
	_imageInfo->frameY = 0;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->frameW = w;
	_imageInfo->frameH = h;
	_type = RENDER_NON;
	_imageName = NULL;
	_trans = false;
	_transColor = RGB(0, 0, 0);
	if (_imageInfo->hB == NULL)
	{
		release();
		return E_FAIL;
	}
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const wchar_t* imageName, float w, float h, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL) release();
	if (imageName == NULL) return E_FAIL;
	HDC hdc = GetDC(_hWnd);
	_imageInfo = new IMAGE_INFO;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hB = (HBITMAP)LoadImage(_hInstance, imageName, IMAGE_BITMAP, w, h, LR_LOADFROMFILE);
	_imageInfo->hOldB = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hB);
	_imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	_imageInfo->hBlendB = (HBITMAP)CreateCompatibleBitmap(hdc, w, h);
	_imageInfo->hBlendOldB = (HBITMAP)SelectObject(_imageInfo->hBlendDC, _imageInfo->hBlendB);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->w = w;
	_imageInfo->h = h;
	_imageInfo->frameX = 0;
	_imageInfo->frameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameW = w / frameX;
	_imageInfo->frameH = h / frameY;
	_imageInfo->alpha = 255;
	_imageInfo->stretch = RectMake(0, 0, w / frameX, h / frameY);
	_imageInfo->loopW = w / frameX;
	_imageInfo->loopH = h / frameY;
	_imageInfo->offSetX = 0;
	_imageInfo->offSetY = 0;
	int len = wcslen(imageName);
	_imageName = new TCHAR[len + 1];
	wcscpy_s(_imageName, len + 1, imageName);
	_trans = trans;
	_transColor = transColor;
	_type = RENDER_NON;
	if (_imageInfo->hB == NULL)
	{
		release();
		return E_FAIL;
	}
	_blendFunction.AlphaFormat = 0;
	_blendFunction.BlendFlags = 0;
	_blendFunction.BlendOp = AC_SRC_OVER;
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOldB);
		DeleteObject(_imageInfo->hB);
		DeleteDC(_imageInfo->hMemDC);
		SelectObject(_imageInfo->hBlendDC, _imageInfo->hBlendOldB);
		DeleteObject(_imageInfo->hBlendB);
		DeleteDC(_imageInfo->hBlendDC);
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_imageName);
		_trans = false;
		_transColor = RGB(0, 0, 0);
	}
}
void image::render(HDC hdc)
{
	if (_type == RENDER_NON)
	{
		if (_trans)
		{
			GdiTransparentBlt(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->frameW, _imageInfo->frameH, _imageInfo->hMemDC,
				_imageInfo->frameW * _imageInfo->frameX, _imageInfo->frameH * _imageInfo->frameY, _imageInfo->frameW, _imageInfo->frameH, _transColor);
		}
		else
		{
			BitBlt(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->frameW, _imageInfo->frameH, _imageInfo->hMemDC, _imageInfo->frameW * _imageInfo->frameX, _imageInfo->frameH * _imageInfo->frameY, SRCCOPY);
		}
	}
	else if (_type == RENDER_BLEND)
	{
		_blendFunction.SourceConstantAlpha = _imageInfo->alpha;
		if (_trans)
		{
			BitBlt(_imageInfo->hBlendDC, 0, 0, _imageInfo->w, _imageInfo->h, hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);
			GdiTransparentBlt(_imageInfo->hBlendDC, 0, 0, _imageInfo->frameW, _imageInfo->frameH, _imageInfo->hMemDC,
				_imageInfo->frameW * _imageInfo->frameX, _imageInfo->frameH * _imageInfo->frameY, _imageInfo->frameW, _imageInfo->frameH, _transColor);
			AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->frameW, _imageInfo->frameH, _imageInfo->hBlendDC,
				0, 0, _imageInfo->frameW, _imageInfo->frameH, _blendFunction);
		}
		else
		{
			AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->frameW, _imageInfo->frameH, _imageInfo->hMemDC,
				_imageInfo->frameW * _imageInfo->frameX, _imageInfo->frameH * _imageInfo->frameY, _imageInfo->frameW, _imageInfo->frameH, _blendFunction);
		}
	}
	else if (_type == RENDER_STRETCH)
	{
		if (_trans)
		{
			BitBlt(_imageInfo->hBlendDC, 0, 0, _imageInfo->w, _imageInfo->h, hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);
			StretchBlt(_imageInfo->hBlendDC, 0, 0, _imageInfo->frameW, _imageInfo->frameH, _imageInfo->hMemDC,
				_imageInfo->frameW * _imageInfo->frameX, _imageInfo->frameH * _imageInfo->frameY, _imageInfo->frameW, _imageInfo->frameH, SRCCOPY);
			GdiTransparentBlt(hdc, _imageInfo->stretch.left, _imageInfo->stretch.top, _imageInfo->stretch.right - _imageInfo->stretch.left, _imageInfo->stretch.bottom - _imageInfo->stretch.top, _imageInfo->hBlendDC,
				0, 0, _imageInfo->frameW, _imageInfo->frameH, _transColor);
		}
		else
		{
			StretchBlt(hdc, _imageInfo->stretch.left, _imageInfo->stretch.top, _imageInfo->stretch.right - _imageInfo->stretch.left, _imageInfo->stretch.bottom - _imageInfo->stretch.top, _imageInfo->hMemDC,
				0, 0, _imageInfo->frameW, _imageInfo->frameH, SRCCOPY);
		}
	}
}
void image::render(HDC hdc, float dx, float dy)
{
	_imageInfo->x = dx;
	_imageInfo->y = dy;
	if (_type == RENDER_NON)
	{
		if (_trans)
		{
			GdiTransparentBlt(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->frameW, _imageInfo->frameH, _imageInfo->hMemDC,
				_imageInfo->frameW * _imageInfo->frameX, _imageInfo->frameH * _imageInfo->frameY, _imageInfo->frameW, _imageInfo->frameH, _transColor);
		}
		else
		{
			BitBlt(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->frameW, _imageInfo->frameH, _imageInfo->hMemDC, _imageInfo->frameW * _imageInfo->frameX, _imageInfo->frameH * _imageInfo->frameY, SRCCOPY);
		}
	}
	else if (_type == RENDER_BLEND)
	{
		_blendFunction.SourceConstantAlpha = _imageInfo->alpha;
		if (_trans)
		{
			BitBlt(_imageInfo->hBlendDC, 0, 0, _imageInfo->w, _imageInfo->h, hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);
			GdiTransparentBlt(_imageInfo->hBlendDC, 0, 0, _imageInfo->frameW, _imageInfo->frameH, _imageInfo->hMemDC,
				_imageInfo->frameW * _imageInfo->frameX, _imageInfo->frameH * _imageInfo->frameY, _imageInfo->frameW, _imageInfo->frameH, _transColor);
			AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->frameW, _imageInfo->frameH, _imageInfo->hBlendDC,
				0, 0, _imageInfo->frameW, _imageInfo->frameH, _blendFunction);
		}
		else
		{
			AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->frameW, _imageInfo->frameH, _imageInfo->hMemDC,
				_imageInfo->frameW * _imageInfo->frameX, _imageInfo->frameH * _imageInfo->frameY, _imageInfo->frameW, _imageInfo->frameH, _blendFunction);
		}
	}
	else if (_type == RENDER_STRETCH)
	{
		if (_trans)
		{
			BitBlt(_imageInfo->hBlendDC, 0, 0, _imageInfo->w, _imageInfo->h, hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);
			StretchBlt(_imageInfo->hBlendDC, 0, 0, _imageInfo->frameW, _imageInfo->frameH, _imageInfo->hMemDC,
				_imageInfo->frameW * _imageInfo->frameX, _imageInfo->frameH * _imageInfo->frameY, _imageInfo->frameW, _imageInfo->frameH, SRCCOPY);
			GdiTransparentBlt(hdc, _imageInfo->stretch.left, _imageInfo->stretch.top, _imageInfo->stretch.right - _imageInfo->stretch.left, _imageInfo->stretch.bottom - _imageInfo->stretch.top, _imageInfo->hBlendDC,
				0, 0, _imageInfo->frameW, _imageInfo->frameH, _transColor);

		}
		else
		{
			StretchBlt(hdc, _imageInfo->stretch.left, _imageInfo->stretch.top, _imageInfo->stretch.right - _imageInfo->stretch.left, _imageInfo->stretch.bottom - _imageInfo->stretch.top, _imageInfo->hMemDC,
				0, 0, _imageInfo->frameW, _imageInfo->frameH, SRCCOPY);
		}
	}
}
void image::render(HDC hdc, float x, float y, float w, float h)
{
	if (_type == RENDER_NON)
	{
		if (_trans)
		{
			GdiTransparentBlt(hdc, _imageInfo->x, _imageInfo->y, w, h, _imageInfo->hMemDC, x, y, w, h, _transColor);
		}
		else
		{
			BitBlt(hdc, _imageInfo->x, _imageInfo->y, w, h, _imageInfo->hMemDC, x, y, SRCCOPY);
		}
	}
	else if (_type == RENDER_BLEND)
	{
		_blendFunction.SourceConstantAlpha = _imageInfo->alpha;
		if (_trans)
		{
			BitBlt(_imageInfo->hBlendDC, 0, 0, _imageInfo->w, _imageInfo->h, hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);
			GdiTransparentBlt(_imageInfo->hBlendDC, 0, 0, w, h, _imageInfo->hMemDC,
				x, y, w, h, _transColor);
			AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, w, h, _imageInfo->hBlendDC,
				0, 0, w, h, _blendFunction);
		}
		else
		{
			AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, w, h, _imageInfo->hMemDC,
				x, y, w, h, _blendFunction);
		}
	}
	else if (_type == RENDER_STRETCH)
	{
		if (_trans)
		{
			BitBlt(_imageInfo->hBlendDC, 0, 0, _imageInfo->w, _imageInfo->h, hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);
			StretchBlt(_imageInfo->hBlendDC, 0, 0, w, h, _imageInfo->hMemDC,
				x, y, w, h, SRCCOPY);
			GdiTransparentBlt(hdc, _imageInfo->stretch.left, _imageInfo->stretch.top, _imageInfo->stretch.right - _imageInfo->stretch.left, _imageInfo->stretch.bottom - _imageInfo->stretch.top, _imageInfo->hBlendDC,
				0, 0, _imageInfo->frameW, _imageInfo->frameH, _transColor);

		}
		else
		{
			StretchBlt(hdc, _imageInfo->stretch.left, _imageInfo->stretch.top, _imageInfo->stretch.right - _imageInfo->stretch.left, _imageInfo->stretch.bottom - _imageInfo->stretch.top, _imageInfo->hMemDC,
				x, y, w, h, SRCCOPY);
		}
	}
}
void image::render(HDC hdc, float dx, float dy, float x, float y, float w, float h)
{
	_imageInfo->x = dx;
	_imageInfo->y = dy;
	if (_type == RENDER_NON)
	{
		if (_trans)
		{
			GdiTransparentBlt(hdc, _imageInfo->x, _imageInfo->y, w, h, _imageInfo->hMemDC, x, y, w, h, _transColor);
		}
		else
		{
			BitBlt(hdc, _imageInfo->x, _imageInfo->y, w, h, _imageInfo->hMemDC, x, y, SRCCOPY);
		}
	}
	else if (_type == RENDER_BLEND)
	{
		_blendFunction.SourceConstantAlpha = _imageInfo->alpha;
		if (_trans)
		{
			BitBlt(_imageInfo->hBlendDC, 0, 0, _imageInfo->w, _imageInfo->h, hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);
			GdiTransparentBlt(_imageInfo->hBlendDC, 0, 0, w, h, _imageInfo->hMemDC,
				x, y, w, h, _transColor);
			AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, w, h, _imageInfo->hBlendDC,
				0, 0, w, h, _blendFunction);
		}
		else
		{
			AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, w, h, _imageInfo->hMemDC,
				x, y, w, h, _blendFunction);
		}
	}
	else if (_type == RENDER_STRETCH)
	{
		if (_trans)
		{
			BitBlt(_imageInfo->hBlendDC, 0, 0, _imageInfo->w, _imageInfo->h, hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);
			StretchBlt(_imageInfo->hBlendDC, 0, 0, w, h, _imageInfo->hMemDC,
				x, y, w, h, SRCCOPY);
			GdiTransparentBlt(hdc, _imageInfo->stretch.left, _imageInfo->stretch.top, _imageInfo->stretch.right - _imageInfo->stretch.left, _imageInfo->stretch.bottom - _imageInfo->stretch.top, _imageInfo->hBlendDC,
				0, 0, _imageInfo->frameW, _imageInfo->frameH, _transColor);

		}
		else
		{
			StretchBlt(hdc, _imageInfo->stretch.left, _imageInfo->stretch.top, _imageInfo->stretch.right - _imageInfo->stretch.left, _imageInfo->stretch.bottom - _imageInfo->stretch.top, _imageInfo->hMemDC,
				x, y, w, h, SRCCOPY);
		}
	}
}
void image::loop(HDC hdc)
{
	if (_imageInfo->offSetX < 0) _imageInfo->offSetX = _imageInfo->frameW + (_imageInfo->offSetX % (int)_imageInfo->frameW);
	if (_imageInfo->offSetY < 0) _imageInfo->offSetY = _imageInfo->frameH + (_imageInfo->offSetY % (int)_imageInfo->frameH);
	RECT rc, sR;
	float sW, sH;
	for (int y = 0; y < _imageInfo->loopH; y += sH)
	{
		sR.top = (y + _imageInfo->offSetY) % (int)_imageInfo->frameH;
		sR.bottom = (int)_imageInfo->frameH;
		sH = sR.bottom - sR.top;
		if (y + sH > _imageInfo->loopH)
		{
			sR.bottom -= (y + sH) - _imageInfo->loopH;
			sH = sR.bottom - sR.top;
		}
		rc.top = y + _imageInfo->y;
		rc.bottom = rc.top + sH;
		for (int x = 0; x < _imageInfo->loopW; x += sW)
		{
			sR.left = (x + _imageInfo->offSetX) % (int)_imageInfo->frameW;
			sR.right = _imageInfo->frameW;
			sW = sR.right - sR.left;
			if (x + sW > _imageInfo->loopW)
			{
				sR.right -= (x + sW) - _imageInfo->loopW;
				sW = sR.right - sR.left;
			}
			rc.left = x + _imageInfo->x;
			rc.right = rc.left + sW;
			this->render(hdc, rc.left, rc.top, sR.left, sR.top, sR.right - sR.left, sR.bottom - sR.top);
		}
	}
}
void image::loop(HDC hdc, float dx, float dy, float w, float h, int offSetX, int offSetY)
{
	if (offSetX < 0) offSetX = _imageInfo->w + (offSetX % (int)_imageInfo->w);
	if (offSetY < 0) offSetY = _imageInfo->h + (offSetY % (int)_imageInfo->h);
	RECT rc, sR;
	float sW, sH;
	for (int y = 0; y < h; y += sH)
	{
		sR.top = (y + offSetY) % (int)_imageInfo->h;
		sR.bottom = (int)_imageInfo->h;
		sH = sR.bottom - sR.top;
		if (y + sH > h)
		{
			sR.bottom -= (y + sH) - h;
			sH = sR.bottom - sR.top;
		}
		rc.top = y + dy;
		rc.bottom = rc.top + sH;
		for (int x = 0; x < w; x += sW)
		{
			sR.left = (x + offSetX) % (int)_imageInfo->w;
			sR.right = _imageInfo->w;
			sW = sR.right - sR.left;
			if (x + sW > w)
			{
				sR.right -= (x + sW) - w;
				sW = sR.right - sR.left;
			}
			rc.left = x + dx;
			rc.right = rc.left + sW;
			this->render(hdc, rc.left, rc.top, sR.left, sR.top, sR.right - sR.left, sR.bottom - sR.top);
		}
	}
}
void image::zoom(HDC hdc)
{
	BitBlt(_imageInfo->hBlendDC, 0, 0, WINSIZEX, WINSIZEY, hdc, 0, 0, SRCCOPY);
	StretchBlt(_imageInfo->hBlendDC, 0, 0, WINSIZEX, WINSIZEY, _imageInfo->hMemDC,
		0, 0, WINSIZEX, WINSIZEY, SRCCOPY);
	GdiTransparentBlt(hdc, _imageInfo->stretch.left, _imageInfo->stretch.top, _imageInfo->stretch.right - _imageInfo->stretch.left, _imageInfo->stretch.bottom - _imageInfo->stretch.top, _imageInfo->hBlendDC,
		0, 0, WINSIZEX, WINSIZEY, _transColor);
}
void image::frameRender(HDC hdc, animation* frame)
{
	this->render(hdc, frame->getFramePos().x, frame->getFramePos().y, frame->getFrameW(), frame->getFrameH());
}
void image::frameRender(HDC hdc, float dx, float dy, animation* frame)
{
	this->render(hdc, dx, dy, frame->getFramePos().x, frame->getFramePos().y, frame->getFrameW(), frame->getFrameH());
}