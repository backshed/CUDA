#include<iostream>
#include<random>
#include<time.h>
#include<Windows.h>
#include"Buffer.h"
#include"Blas.h"
#include"RNG.h"
#include"StopWatch.h"
int main(int argc, char**argv) {

	using namespace std;
	typedef float value_t;

	int const D = 1024;
	int const M = D;
	int const N = D*D;
	int const K = D;

	value_t const one = 1;
	value_t const zero = 0;

	Buffer<value_t>A(M*K);
	Buffer<value_t>B(K*N);
	Buffer<value_t>C(M*N);

	RNG rng;

	Blas engine;

	StopWatch watch;
	watch.start();

	double err = 0.0;
	for (int j = 0, J = 1024; j < J; ++j) {
		rng.uniform(&A);
		rng.uniform(&B);
		engine.gemm(&C, M, A, M, B, K, one, zero, M, N, K);
	}
	cout << "Elapsed time: " << watch.stop() << " second" << endl;

	return 0;
}