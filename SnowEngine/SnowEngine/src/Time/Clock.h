#pragma once

namespace Snow {
	class Clock {
	private:
		float m_StartTime;
		float m_Elapsed;
	public:
		float StartTime() { return m_StartTime; }
		float Elapsed() { return m_Elapsed; }

		void Start();
		void Stop();
		void Update();
	};
}