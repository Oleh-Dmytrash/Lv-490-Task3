#include "Timer.h"

void Timer::Start()
{
	m_start_time = std::chrono::steady_clock::now();
}

long long Timer::GetTimePassed()
{
	std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - m_start_time).count();
}