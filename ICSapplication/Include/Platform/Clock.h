#pragma once

#include <chrono>

class Clock
{
public:
	struct Time
	{
		float Elapsed;
		float PreviousFrame;
	};
public:
	Clock();

	void OnUpdate();
public:
	Time time;

private:
	std::chrono::high_resolution_clock m_Clock;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
};
