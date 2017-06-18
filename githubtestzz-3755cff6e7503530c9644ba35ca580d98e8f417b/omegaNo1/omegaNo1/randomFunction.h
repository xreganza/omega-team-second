#pragma once
#include "singletonBase.h"
#include <time.h>
class randomFunction : public singletonBase<randomFunction>
{
public:

	randomFunction()
	{
		srand(GetTickCount());
	};
	~randomFunction() {};

	inline int intUnder(int num) { return rand() % num; }
	
};

