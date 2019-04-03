//Code from moodle

#include "Timer.h"

LowResTimer::LowResTimer()
{

}

void LowResTimer::startTimer()
{
	timer = clock();
}

double LowResTimer::getTime()
{
	return ((double)(clock() - timer)) / CLOCKS_PER_SEC;
}

void LowResTimer::resetTimer()
{
	startTimer();
}
