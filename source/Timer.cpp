#include "GLFW/glfw3.h"
#include "Timer.h"

void Timer::Update()
{
	m_current_time = static_cast<float>(glfwGetTime());
	m_delta_time = m_current_time - m_last_time;
	m_last_time = m_current_time;
	m_frames++;
	m_new_second = false;
	if (m_current_time - m_last_second >= 1.0f)
	{
		m_new_second = true;
		m_last_second = m_current_time;
		m_frames_in_last_second = m_frames;
		m_frames = 0;
	}
}

bool Timer::IsNewSecond() const
{
	return m_new_second;
}

unsigned int Timer::GetFramesInLastSecond() const
{
	return m_frames_in_last_second;
}

float Timer::GetDeltaTime() const
{
	return m_delta_time;
}
