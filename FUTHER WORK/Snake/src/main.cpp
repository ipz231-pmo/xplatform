#include "main.hpp"


#include <cstdio>
#include <fstream>




int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	while (true)
	{
		auto stop = std::chrono::high_resolution_clock::now();
		auto timeSpan = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		float deltaTime = (float)(timeSpan.count()) / 1'000;
		start = stop;
	}
	


}