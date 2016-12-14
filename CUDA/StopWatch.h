#pragma once
class StopWatch
{
private:
	void*const ref;
public:
	StopWatch();
	~StopWatch();
	double start();
	double wrap();
	double stop();
};

