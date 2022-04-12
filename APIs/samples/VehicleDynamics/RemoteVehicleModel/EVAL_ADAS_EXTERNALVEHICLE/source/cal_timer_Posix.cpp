
#ifndef _WIN32

#include "cal_timer.h"
//#include <windows.h>
#include <time.h>

struct TimerData
{
	TimerData() {}
	//_LARGE_INTEGER frequency;
	//_LARGE_INTEGER previous_time;
	time_t previous_time;
};

Timer::Timer() : m_data(NULL)
{
	Init();
}

void Timer::Init()
{
	delete m_data;
	m_data = new TimerData();
	//QueryPerformanceFrequency(&m_data->frequency);
	//QueryPerformanceCounter(&m_data->previous_time);
	time(&m_data->previous_time);
}

Timer::~Timer()
{
	delete m_data;
}

double Timer::Event()
{
	//_LARGE_INTEGER old_time = m_data->previous_time;
	//QueryPerformanceCounter(&m_data->previous_time);
	//double DeltaT = double(m_data->previous_time.QuadPart-old_time.QuadPart)/double(m_data->frequency.QuadPart);
	//return DeltaT;

	time_t old_time = m_data->previous_time;
	time(&m_data->previous_time);
	double DeltaT = difftime(m_data->previous_time,old_time);
	return DeltaT;
}

double Timer::TimeSinceLastEvent()
{
	//_LARGE_INTEGER current_time;
	//QueryPerformanceCounter(&current_time);
	//return double(current_time.QuadPart-m_data->previous_time.QuadPart)/double(m_data->frequency.QuadPart);

	time_t current_time;
	time(&current_time);
	return difftime(current_time,m_data->previous_time);
}


void SleepSeconds(double t)
{
	//Sleep(unsigned long(t*1000.0));
}

#endif //_WIN32
