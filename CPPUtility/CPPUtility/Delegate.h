#pragma once 
#include <iostream>
#include <vector>
#include <assert.h>

#include "Object.h"

template <typename T, typename... args>
class Delegate
{
	std::vector<T (Object::*)(args...)> dgt;

	U* instance = nullptr;

public:

	Delegate();
	~Delegate();

	void Invoke(args... _args);

	bool Exist(T Object::*_method(args...));

	void Subscribe(Object* _instance, T Object::*_method(args...));

	void Unsubscribe(T Object::*_method(args...));
};



template<typename T, typename ...args>
inline Delegate<T, args...>::Delegate()
{
}

template<typename T, typename ...args>
inline Delegate<T, args...>::~Delegate()
{
}

template<typename T, typename ...args>
inline void Delegate<T, args...>::Invoke(args... _args)
{
	for (int i = 0; i < dgt.size(); i++)
		instance->dgt[i](_args...);
	
}

template<typename T, typename ...args>
inline bool Delegate<T, args...>::Exist(T Object::*_method(args...))
{
	for (int i = 0; i < dgt.size(); i++)
	{
		if (dgt[i] == *_method)
			return true;
	}

	return false;
}

template<typename T, typename ...args>
inline void Delegate<T, args...>::Subscribe(Object* _instance, T Object::*_method(args...))
{
	if (instance == nullptr)
		instance = _instance;

	dgt.push_back(*_method);
}

template<typename T, typename ...args>
inline void Delegate<T, args...>::Unsubscribe(T Object::*_method(args...))
{
	assert(("Method doesn't exist in this delegate", Exist(_method)));

	for (int i = 0; i < dgt.size(); i++)
	{
		if (dgt[i] == *_method)
		{
			dgt.erase(dgt.begin() + i);
			return;
		}
	}

}