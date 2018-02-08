#pragma once
#include <sys/time.h>

class Timer {
public:
	Timer() : _start(), _end() {
	}
	
	void Start() {
		gettimeofday(&_start, NULL);
	}

	void Stop() {
		gettimeofday(&_end, NULL);
	}

	double GetElapsedMillseconds() {
		return (_end.tv_sec - _start.tv_sec) * 1000.0
			+ (_end.tv_usec - _start.tv_usec) / 1000.0 ;
	}

private:
	struct timeval _start;
	struct timeval _end;
};
