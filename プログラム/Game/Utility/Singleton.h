#pragma once

template<class T> class Singleton
{
public:
	Singleton() {};
	virtual ~Singleton() {};

public:
	static T& GetInstace()
	{
		static T instance;
		return instance;
	}
};
