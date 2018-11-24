#pragma once

template< class T >
class Singleton
{
public:
	Singleton() {}
	virtual ~Singleton() {}

	static T* GetInstance()
	{
		static T sInstance;
		return &sInstance;
	}
};