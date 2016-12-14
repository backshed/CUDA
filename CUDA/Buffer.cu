#include<iostream>
#include<cuda_runtime_api.h>
#include"Buffer.h"

template<typename T>inline T min(T a, T b) {
	return a < b ? a : b;
}

inline void*mallocuda(size_t const size) {
	void*result = 0;
	if (cudaMalloc(&result, size) != cudaSuccess)result = 0;
	return result;
}

template<typename T>Buffer<T>::Buffer(size_t const reserve)throw(int) :length(reserve), devptr((T*)mallocuda(sizeof(T)*reserve)) {
	if (devptr)cudaMemset(devptr, 0, sizeof(T)*length);
	else {
		using namespace std;
		cerr << "damepo" << endl; exit(-1);
	}
}

template<typename T>Buffer<T>::Buffer(const Buffer<T>&ref) : Buffer(ref.length) {
	if (devptr)cudaMemcpy(devptr, ref.devptr, sizeof(T)*length, cudaMemcpyDeviceToDevice);
}

template<typename T>Buffer<T>::Buffer(std::vector<T>&vector) : Buffer(vector.size()) {
	if (devptr)cudaMemcpy(devptr, vector.data(), sizeof(T)*length, cudaMemcpyHostToDevice);
}

template<typename T>Buffer<T>::~Buffer() {
	if (devptr)cudaFree(devptr);
}

template<typename T>Buffer<T>::operator std::vector<T>()const {
	std::vector<T>result(length);
	if (devptr)cudaMemcpy(result.data(), devptr, sizeof(T)*min<const size_t>(length, result.size()), cudaMemcpyDeviceToHost);
	return result;
}

template<typename T>Buffer<T>&Buffer<T>::operator=(const std::vector<T>&vector) {
	if (devptr)cudaMemcpy(devptr, vector.data(), sizeof(T)*min<const size_t>(length, vector.size()), cudaMemcpyHostToDevice);
	return*this;
}

template<typename T>std::size_t Buffer<T>::size()const {
	return length;
}

template<typename T>const T*Buffer<T>::data()const {
	return devptr;
}

template<typename T>void __global__ add(T*const c, const T*a, const T*const b) {
	std::size_t const idx = threadIdx.x;
	c[idx] = a[idx] + b[idx];
}

template<typename T>void __global__ sub(T*const c, const T*a, const T*const b, size_t const length) {
	std::size_t const idx = threadIdx.x;
	if (idx < length)c[idx] = a[idx] - b[idx];
}

template<typename T>void __global__ mul(T*const c, const T*a, const T*const b) {
	std::size_t const idx = threadIdx.x;
	c[idx] = a[idx] * b[idx];
}

template<typename T>void __global__ div(T*const c, const T*a, const T*const b) {
	std::size_t const idx = threadIdx.x;
	c[idx] = a[idx] / b[idx];
}

template<typename T>Buffer<T>operator+(const Buffer<T>&a, const Buffer<T>&b) {
	std::size_t const length = min<std::size_t>(a.size(), b.size());
	Buffer<T>c(length);
	add<T> << <1, length >> > ((T*)c.data(), a.data(), b.data());
	return c;
}

template<typename T>Buffer<T>operator-(const Buffer<T>&a, const Buffer<T>&b) {
	std::size_t const length = min<std::size_t>(a.size(), b.size());
	Buffer<T>c(length);
	sub<T> << <(length - 1) / 64 + 1, 64 >> > ((T*)c.data(), a.data(), b.data(), length);
	return c;
}

template<typename T>Buffer<T>operator*(const Buffer<T>&a, const Buffer<T>&b) {
	std::size_t const length = min<std::size_t>(a.size(), b.size());
	Buffer<T>c(length);
	mul<T> << <1, length >> > ((T*)c.data(), a.data(), b.data());
	return c;
}

template<typename T>Buffer<T>operator/(const Buffer<T>&a, const Buffer<T>&b) {
	std::size_t const length = min<std::size_t>(a.size(), b.size());
	Buffer<T>c(length);
	div<T> << <1, length >> > ((T*)c.data(), a.data(), b.data());
	return c;
}

template<typename T>void __global__ sin(T*const y) {
	std::size_t const idx = threadIdx.x;
	y[idx] = sin(y[idx]);
}

template<typename T>void __global__ cos(T*const y) {
	std::size_t const idx = threadIdx.x;
	y[idx] = cos(y[idx]);
}

template<typename T>void __global__ tan(T*const y) {
	std::size_t const idx = threadIdx.x;
	y[idx] = tan(y[idx]);
}

template<typename T>Buffer<T>sin(const Buffer<T>&x) {
	Buffer<T>y(x);
	sin<T> << <1, y.size() >> > ((T*)y.data());
	return y;
}

template<typename T>Buffer<T>cos(const Buffer<T>&x) {
	Buffer<T>y(x);
	cos<T> << <1, y.size() >> > ((T*)y.data());
	return y;
}

template<typename T>Buffer<T>tan(const Buffer<T>&x) {
	Buffer<T>y(x);
	tan<T> << <1, y.size() >> > ((T*)y.data());
	return y;
}

template<typename T>void __global__ exp(T*const y) {
	std::size_t const idx = threadIdx.x;
	y[idx] = exp(y[idx]);
}

template<typename T>void __global__ log(T*const y) {
	std::size_t const idx = threadIdx.x;
	y[idx] = log(y[idx]);
}

template<typename T>Buffer<T>exp(const Buffer<T>&x) {
	Buffer<T>y(x);
	exp<T> << <1, y.size() >> > ((T*)y.data());
	return y;
}

template<typename T>Buffer<T>log(const Buffer<T>&x) {
	Buffer<T>y(x);
	log<T> << <1, y.size() >> > ((T*)y.data());
	return y;
}


#define T float
template Buffer<T>;
template Buffer<T>operator+(const Buffer<T>&, const Buffer<T>&);
template Buffer<T>operator-(const Buffer<T>&, const Buffer<T>&);
template Buffer<T>operator*(const Buffer<T>&, const Buffer<T>&);
template Buffer<T>operator/(const Buffer<T>&, const Buffer<T>&);
template Buffer<T>sin(const Buffer<T>&);
template Buffer<T>cos(const Buffer<T>&);
template Buffer<T>tan(const Buffer<T>&);
template Buffer<T>exp(const Buffer<T>&);
template Buffer<T>log(const Buffer<T>&);

#undef T

#define T double
template Buffer<T>;
template Buffer<T>operator+(const Buffer<T>&, const Buffer<T>&);
template Buffer<T>operator-(const Buffer<T>&, const Buffer<T>&);
template Buffer<T>operator*(const Buffer<T>&, const Buffer<T>&);
template Buffer<T>operator/(const Buffer<T>&, const Buffer<T>&);
template Buffer<T>sin(const Buffer<T>&);
template Buffer<T>cos(const Buffer<T>&);
template Buffer<T>tan(const Buffer<T>&);
template Buffer<T>exp(const Buffer<T>&);
template Buffer<T>log(const Buffer<T>&);
#undef T
