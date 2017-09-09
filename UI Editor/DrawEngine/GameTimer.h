#ifndef GAME_TIMER_H
#define GAME_TIMER_H

/*
 * 文件名：GameTimer
 * 作用：用来进行时间更新，这里不考虑暂停等情况
 */

class GameTimer
{
public:
	GameTimer();

	float totalTime() const;			// in seconds
	float deltaTime() const;			// in seconds

	void reset();					// Call before message loop.
	void tick();					// Call every frame

private:
	double m_secondsPerCount;
	double m_deltaTime;

	__int64 m_baseTime;
	__int64 m_prevTime;
	__int64 m_currTime;
};

#endif	// GAME_TIMER_H