#pragma once
#include<vector>
template<typename T>
class Buffer
{
private:
protected:
	T*const devptr;
	const std::size_t length;
public:
private:
protected:
public:
	Buffer(std::size_t const)throw(int);
	Buffer(std::vector<T>&);
	Buffer(const Buffer<T>&);
	explicit operator std::vector<T>()const;
	Buffer&operator=(const std::vector<T>&);
	~Buffer();
	std::size_t size()const;
	const T*data()const;
};
template<typename T>Buffer<T>operator+(const Buffer<T>&, const Buffer<T>&);
template<typename T>Buffer<T>operator-(const Buffer<T>&, const Buffer<T>&);
template<typename T>Buffer<T>operator*(const Buffer<T>&, const Buffer<T>&);
template<typename T>Buffer<T>operator/(const Buffer<T>&, const Buffer<T>&);

template<typename T>Buffer<T>sin(const Buffer<T>&);
template<typename T>Buffer<T>cos(const Buffer<T>&);
template<typename T>Buffer<T>tan(const Buffer<T>&);

template<typename T>Buffer<T>exp(const Buffer<T>&);
template<typename T>Buffer<T>log(const Buffer<T>&);
