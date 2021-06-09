#pragma once
#include <vector>

class Object
{
protected:

	template<typename T, typename... args>
	T MainMethod(args...) = 0;



};

