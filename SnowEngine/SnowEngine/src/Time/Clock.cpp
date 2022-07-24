#include "snowpch.h"
#include "Clock.h"
#include "src/Platform/Platform.h" 

namespace Snow {
	void Clock::Start()
	{
		m_StartTime = platform_GetAbsTime();
		m_Elapsed = 0;
	}
	void Clock::Stop()
	{
		m_StartTime = 0;
	}
	void Clock::Update()
	{
		if (m_StartTime != 0) {
			m_Elapsed = platform_GetAbsTime() - m_StartTime;
		}
	}
}