#pragma once
#include "singletonBase.h"
#include <vector>
#include <string>
class txtData : public singletonBase<txtData>
{
public:
	txtData();
	~txtData();
	HRESULT init();
	void release();
	void txtSave(const wchar_t* saveName, vector<wstring> vStr);
	wchar_t* vectorArrayCombine(vector<wstring> vArray);
	vector<wstring> txtLoad(const wchar_t* loadName);
	vector<wstring> charArraySeparation(wchar_t charArray[]);
};

