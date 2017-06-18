#pragma once
#include <math.h>
#define PI 3.141592653
#define PI8 float(PI / 8.0)
#define PI16 float(PI / 16.0)
#define PI32 float(PI / 32.0)
#define PI64 float(PI / 64.0)
#define PI128 float(PI / 128.0)
inline float getDistance(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;
	return sqrtf(x * x + y * y);
}
inline float getAngle(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;
	float d = sqrtf(x * x + y * y);
	float a = acosf(x / d);
	if (y2 > y1)
	{
		a = PI * 2 - a;
		if (a >= PI * 2) a -= PI * 2;
	}
	return a;
}