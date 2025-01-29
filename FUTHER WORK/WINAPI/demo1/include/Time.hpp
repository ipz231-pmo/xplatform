#pragma once

#include <ctime>

namespace Time
{
	void calcDeltaTime();
	extern clock_t startTime, endTime;
	extern double deltaTime;
}