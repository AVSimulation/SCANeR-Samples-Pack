
#pragma once

struct TimerData;

class Timer
{
public:
	Timer();
	~Timer();
	double Event();
	double TimeSinceLastEvent();
	void Init();
private:
	TimerData* m_data;
};

void SleepSeconds(double t);
