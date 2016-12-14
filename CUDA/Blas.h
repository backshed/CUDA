#pragma once
#include"Buffer.h"
class Blas
{
private:
	void*const handle;
protected:
public:
private:
protected:
public:
	Blas();
	~Blas();
	template<typename T>void scal(int, T alpha, Buffer<T>*, int incx)const;
	template<typename T>void axpy(int, T alpha, Buffer<T>*, int incx, Buffer<T>*, int)const;
	template<typename T>T dot(const Buffer<T>&, int, const Buffer<T>&, int)const;
	template<typename T>void gemv(Buffer<T>*, int, const Buffer<T>&, int, const Buffer<T>&, int, T, T, int, int)const;
	template<typename T>void gemm(Buffer<T>*, int, const Buffer<T>&, int, const Buffer<T>&, int, T, T, int, int, int)const;
};

