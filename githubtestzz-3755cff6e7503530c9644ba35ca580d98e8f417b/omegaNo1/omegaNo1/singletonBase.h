#pragma once
template <typename T>
class singletonBase
{
protected:
	static T* singleton;
	singletonBase() {};
	~singletonBase() {};
public:
	static T* getSingleton()
	{
		if (!singleton)
		{
			singleton = new T;
		}
		return singleton;
	}
	static void releaseSingleton()
	{
		if (singleton)
		{
			delete singleton;
			singleton = 0;
		}
	}
};
template <typename T>
T* singletonBase<T>::singleton = 0;
