#include<curand.h>
#include "RNG.h"

RNG::RNG() :generator(new curandGenerator_t) {
	curandCreateGenerator((curandGenerator_t*)generator, CURAND_RNG_PSEUDO_DEFAULT);
}

RNG::~RNG() {
	curandDestroyGenerator(*(curandGenerator_t*)generator);
	delete(curandGenerator_t*)generator;
}

template<>void RNG::uniform(Buffer<float>*buffer) {
	curandGenerateUniform(*(curandGenerator_t*)generator, (float*)buffer->data(), buffer->size());
}

template<>void RNG::uniform(Buffer<double>*buffer) {
	curandGenerateUniformDouble(*(curandGenerator_t*)generator, (double*)buffer->data(), buffer->size());
}

template<>void RNG::normal(Buffer<float>*buffer, float mean, float stddev) {
	curandGenerateNormal(*(curandGenerator_t*)generator, (float*)buffer->data(), buffer->size(), mean, stddev);
}

template<>void RNG::normal(Buffer<double>*buffer, double mean, double stddev) {
	curandGenerateNormalDouble(*(curandGenerator_t*)generator, (double*)buffer->data(), buffer->size(), mean, stddev);
}