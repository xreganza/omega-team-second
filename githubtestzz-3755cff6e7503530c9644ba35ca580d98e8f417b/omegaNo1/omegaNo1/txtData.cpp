#include "stdafx.h"
#include "txtData.h"
txtData::txtData() {};
txtData::~txtData() {};
HRESULT txtData::init()
{
	return S_OK;
}
void txtData::release()
{

}
void txtData::txtSave(const wchar_t* saveName, vector<wstring> vStr)
{
	HANDLE file;
	TCHAR str[128];
	DWORD write;
	wcsncpy_s(str, 128, vectorArrayCombine(vStr), 126);
	file = CreateFile(saveName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, str, 128, &write, NULL);
	CloseHandle(file);
}
wchar_t* txtData::vectorArrayCombine(vector<wstring> vArray)
{
	TCHAR str[128];
	ZeroMemory(str, sizeof(str));
	for (int i = 0; i < vArray.size(); i++)
	{
		wcsncat_s(str, 128, vArray[i].c_str(), 126);
		if (i + 1 < vArray[i].size()) wcscat(str, L",");
	}
	return str;
}
vector<wstring> txtData::txtLoad(const wchar_t* loadName)
{
	HANDLE file;
	TCHAR str[128];
	DWORD read;
	file = CreateFile(loadName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, str, 128, &read, NULL);
	CloseHandle(file);
	return charArraySeparation(str);
}
vector<wstring> txtData::charArraySeparation(wchar_t charArray[])
{
	vector<wstring> vArray;
	TCHAR* temp;
	TCHAR* separator = L",";
	TCHAR* token;
	token = wcstok(charArray, separator);
	vArray.push_back(token);
	while ((token = wcstok(NULL, separator)) != NULL)
	{
		vArray.push_back(token);
	}
	return vArray;
}