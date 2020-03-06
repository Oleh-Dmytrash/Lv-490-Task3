#pragma once
#include <chrono>
class Timer
{
	std::chrono::steady_clock::time_point m_start_time{};
public:
	void Start();
	long long GetTimePassed();
};

