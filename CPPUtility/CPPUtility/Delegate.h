#pragma once 
#include <iostream>
#include <vector>
#include <assert.h>

#include "Object.h"

template <class U, typename T, typename... args>
class Delegate
{
	std::vector<T(U::*)(args...)> dgt;
	std::vector<T(*)(args...)> dgtStatic;

	U* instance = nullptr;

public:

	Delegate();
	~Delegate();

	void Invoke(args... _args);

	bool Exist(T(U::* _method)(args...));

	void Subscribe(U* _instance, T(U::* _method)(args...));
	void Subscribe(T(*_method)(args...));

	void Unsubscribe(T(U::* _method)(args...));
	void Unsubscribe(T(*_method)(args...));
};

template<class U, typename T, typename ...args>
inline Delegate<U, T, args...>::Delegate()
{
}

template<class U, typename T, typename ...args>
inline Delegate<U, T, args...>::~Delegate()
{
}

template<class U, typename T, typename ...args>
inline void Delegate<U, T, args...>::Invoke(args... _args)
{
	for (int i = 0; i < dgt.size(); i++)
		if (instance)
			(instance->*dgt[i])(_args...);
	
	for (int i = 0; i < dgtStatic.size(); i++)
		(*dgtStatic[i])(_args...);
}

template<class U, typename T, typename ...args>
inline bool Delegate<U, T, args...>::Exist(T(U::* _method)(args...))
{
	for (int i = 0; i < dgt.size(); i++)
	{
		if (dgt[i] == _method)
			return true;
	}

	return false;
}

template<class U, typename T, typename ...args>
inline void Delegate<U, T, args...>::Subscribe(U* _instance, T(U::* _method)(args...))
{
	if (instance == nullptr)
		instance = _instance;

	dgt.push_back(_method);
}

template<class U, typename T, typename ...args>
inline void Delegate<U, T, args...>::Subscribe(T(*_method)(args...))
{
	dgtStatic.push_back(_method);
}

template<class U, typename T, typename ...args>
inline void Delegate<U, T, args...>::Unsubscribe(T(U::* _method)(args...))
{
	assert(("Method doesn't exist in this delegate", Exist(_method)));

	for (int i = 0; i < dgt.size(); i++)
	{
		if (dgt[i] == _method)
		{
			dgt.erase(dgt.begin() + i);
			return;
		}
	}

}

template<class U, typename T, typename ...args>
inline void Delegate<U, T, args...>::Unsubscribe(T(*_method)(args...))
{
	assert(("Method doesn't exist in this delegate", Exist(_method)));

	for (int i = 0; i < dgtStatic.size(); i++)
	{
		if (dgtStatic[i] == _method)
		{
			dgtStatic.erase(dgtStatic.begin() + i);
			return;
		}
	}

}