#include "Platform/Clock.h"

Clock::Clock()
{
	m_Start = m_Clock.now();
}

void Clock::OnUpdate()
{
	std::chrono::duration<float> elapsed = m_Clock.now() - m_Start;
	time.PreviousFrame = elapsed.count() - time.Elapsed;
	time.Elapsed = elapsed.count();
	int x = 0;
}
