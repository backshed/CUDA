#pragma once
#include"Buffer.h"
class RNG
{
protected:
	void*const generator;
public:
	RNG();
	~RNG();
	template<typename T>void uniform(Buffer<T>*);
	template<typename T>void normal(Buffer<T>*, T, T);
};

