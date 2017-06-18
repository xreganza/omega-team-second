#pragma once
inline RECT RectMake(float x, float y, float w, float h)
{
	RECT rc = { x, y, x + w, x + h };
	return rc;
}
inline RECT RectMakeCenter(float x, float y, float w, float h)
{
	RECT rc = { x - w / 2, y - h / 2, x + w / 2, y + h / 2 };
	return rc;
}