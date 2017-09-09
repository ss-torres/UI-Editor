#include "GameTimer.h"
#include <Windows.h>

GameTimer::GameTimer()
	: m_secondsPerCount(0.0), m_deltaTime(-1.0), m_baseTime(0),
	m_prevTime(0), m_currTime(0)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	m_secondsPerCount = 1.0 / static_cast<double>(countsPerSec);
}

float GameTimer::totalTime() const
{
	return static_cast<float>((m_currTime - m_baseTime) * m_secondsPerCount);
}

float GameTimer::deltaTime() const
{
	return static_cast<float>(m_deltaTime);
}

void GameTimer::reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_baseTime = currTime;
	m_prevTime = currTime;
}


void GameTimer::tick()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_currTime = currTime;

	// Time difference between this frame and the previous
	m_deltaTime = (m_currTime - m_prevTime) * m_secondsPerCount;

	// Prepare for next frame.
	m_prevTime = m_currTime;

	// Force nonnegative. The DXSDK's CDXUTTimer mentions that if the 
	// processor goes into a power save mode or we get shuffled to another processor,
	// then mdeltaTime can be negative.
	if (m_deltaTime < 0.0)
	{
		m_deltaTime = 0.0;
	}
}
