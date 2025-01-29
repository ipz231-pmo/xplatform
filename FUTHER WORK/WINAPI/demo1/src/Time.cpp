#include "Time.hpp"

double Time::deltaTime;
clock_t Time::startTime, Time::endTime;


void Time::calcDeltaTime()
{
	endTime = clock();
	deltaTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	startTime = endTime;
}