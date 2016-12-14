#include<Windows.h>
#include"StopWatch.h"

StopWatch::StopWatch() :ref(new LARGE_INTEGER[4]) {
	QueryPerformanceFrequency(((LARGE_INTEGER*)ref) + 3);
}

StopWatch::~StopWatch() {
	delete[](LARGE_INTEGER*)ref;
}

double StopWatch::start() {
	QueryPerformanceCounter(((LARGE_INTEGER*)ref) + 2);
	((LARGE_INTEGER*)ref)[1].QuadPart = ((LARGE_INTEGER*)ref)[2].QuadPart;
	return 0;
}

double StopWatch::wrap() {
	QueryPerformanceCounter(((LARGE_INTEGER*)ref) + 0);
	double const result = (((LARGE_INTEGER*)ref)[0].QuadPart - ((LARGE_INTEGER*)ref)[1].QuadPart) / (double)((LARGE_INTEGER*)ref)[3].QuadPart;
	((LARGE_INTEGER*)ref)[1].QuadPart = ((LARGE_INTEGER*)ref)[0].QuadPart;
	return result;
}

double StopWatch::stop() {
	QueryPerformanceCounter(((LARGE_INTEGER*)ref) + 0);
	double const result = (((LARGE_INTEGER*)ref)[0].QuadPart - ((LARGE_INTEGER*)ref)[2].QuadPart) / (double)((LARGE_INTEGER*)ref)[3].QuadPart;
	return result;
}
