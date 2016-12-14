#include<iostream>
#include<cublas.h>
#include"Blas.h"

template<typename T>T min(T a, T b) {
	return a < b ? a : b;
}

Blas::Blas() :handle(new cublasHandle_t) {
	cublasCreate_v2((cublasHandle_t*)handle);
}

Blas::~Blas() {
	cublasDestroy_v2(*(cublasHandle_t*)handle);
	delete(cublasHandle_t*)handle;
}

template<> float Blas::dot(const Buffer<float>&x, int incx, const Buffer<float>&y, int incy)const {
	float result = 0;
	cublasSdot_v2(*(cublasHandle_t*)handle, min<size_t>(x.size(), y.size()), x.data(), incx, y.data(), incy, &result);
	return result;
}

template<> double Blas::dot(const Buffer<double>&x, int incx, const Buffer<double>&y, int incy)const {
	double result = 0;
	cublasDdot_v2(*(cublasHandle_t*)handle, min<size_t>(x.size(), y.size()), x.data(), incx, y.data(), incy, &result);
	return result;
}

template<>void Blas::gemv(Buffer<float>*y, int incy, const Buffer<float>&A, int lda, const Buffer<float>&x, int incx, float alpha, float beta, int m, int n)const {
	cublasSgemv_v2(*(cublasHandle_t*)handle, CUBLAS_OP_N, m, n, &alpha, A.data(), lda, x.data(), incx, &beta, (float*)y->data(), incy);
}

template<>void Blas::gemv(Buffer<double>*y, int incy, const Buffer<double>&A, int lda, const Buffer<double>&x, int incx, double alpha, double beta, int m, int n)const {
	cublasDgemv_v2(*(cublasHandle_t*)handle, CUBLAS_OP_N, m, n, &alpha, A.data(), lda, x.data(), incx, &beta, (double*)y->data(), incy);
}

template<> void Blas::gemm(Buffer<float>*C, int ldc, const Buffer<float>&A, int lda, const Buffer<float>&B, int ldb, float alpha, float beta, int m, int n, int k)const {
	cublasSgemm_v2(*(cublasHandle_t*)handle, CUBLAS_OP_N, CUBLAS_OP_N, m, n, k, &alpha, A.data(), lda, B.data(), ldb, &beta, (float*)C->data(), ldc);
}

template<> void Blas::gemm(Buffer<double>*C, int ldc, const Buffer<double>&A, int lda, const Buffer<double>&B, int ldb, double alpha, double beta, int m, int n, int k)const {
	cublasDgemm_v2(*(cublasHandle_t*)handle, CUBLAS_OP_N, CUBLAS_OP_N, m, n, k, &alpha, A.data(), lda, B.data(), ldb, &beta, (double*)C->data(), ldc);
}

template<> void Blas::scal(int n, float alpha, Buffer<float>*x, int incx)const { 
	cublasSscal_v2(*(cublasHandle_t*)handle, n, &alpha, (float*)x->data(), incx); 
}

template<> void Blas::scal(int n, double alpha, Buffer<double>*x, int incx)const { 
	cublasDscal_v2(*(cublasHandle_t*)handle, n, &alpha, (double*)x->data(), incx); 
}

template<> void Blas::axpy(int n, float alpha, Buffer<float>*x, int incx, Buffer<float>*y, int incy)const { 
	cublasSaxpy_v2(*(cublasHandle_t*)handle, n, &alpha, (float*)x->data(), incx, (float*)y->data(), incy); 
}

template<> void Blas::axpy(int n, double alpha, Buffer<double>*x, int incx, Buffer<double>*y, int incy)const { 
	cublasDaxpy_v2(*(cublasHandle_t*)handle, n, &alpha, (double*)x->data(), incx, (double*)y->data(), incy); 
}

