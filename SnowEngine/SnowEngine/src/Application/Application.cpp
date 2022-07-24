#include "snowpch.h"
#include "Application.h"

#include "../Memory/Memory.h"


#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Snow::Application::Application(ApplicationSpecification spec)
{
	WindowSpecification windowSpec{spec.Name, spec.WindowWidth, spec.WindowHeight};
	windowSpec.x = spec.WindowX;
	windowSpec.y = spec.WindowY;
	SNOW_INFO("Creating window (%s): %i, %i", spec.Name, spec.WindowWidth, spec.WindowHeight);

	m_Spec = spec;

	m_Window = new Window(windowSpec, &m_State);
	m_Clock = Clock();
	Memory::MemInit();

	if (!m_Renderer.Init(spec.Name, &m_State)) {
		SNOW_FATAL("Failed to init renderer");
	}

	if (!m_Instance)
		m_Instance = this;
}

Snow::Application::~Application()
{
	delete m_Window;
	Memory::MemShutdown();
	m_Renderer.Shutdown();
}

void Snow::Application::Run()
{
	m_Clock.Start();
	float lastTime = m_Clock.Elapsed();
	float frameCount = 0;
	//int currTime = 0;
	float targetFrames = 1.0f / m_Spec.FrameCap;

	while (m_Running) {
		m_Clock.Update();
		float currTime = m_Clock.Elapsed();
		float delta = currTime - lastTime;
		lastTime = currTime;
		float frameStart = platform_GetAbsTime();

		if (!platform_PumpMessages(&m_State)) {
			m_Running = false;
		}

		OnUpdate(DeltaTime(delta));
		RenderCommand command;
		command.deltaTime = DeltaTime(delta);
		m_Renderer.DrawFrame(&command);

		float frameEnd = platform_GetAbsTime();
		float frameTime = frameEnd - frameStart;
		float deltaSeconds = targetFrames - frameTime;	

		if (deltaSeconds > 0) {
			unsigned int remainingms = deltaSeconds * 1000;

			bool limitFrameRate = m_Spec.LimitFramerate;
			if (limitFrameRate && remainingms > 0) {
				platform_Sleep(remainingms - 1);
			}
			frameCount++;
		}
	}
}

bool Snow::Application::OnWindowClose(Event& e)
{
	m_Running = false;
	return false;
}

bool Snow::Application::OnWindowResized(Event& e)
{
	return false;
}

void Snow::Application::OnEvent(Event& e)
{
	switch (e.GetEventType()) {
		case (EventType::WindowClose):
		{
			OnWindowClose(e);
			break;
		}
		case (EventType::WindowResize):
		{
			OnWindowClose(e);
			break;
		}
	}
}

Snow::ApplicationSpecification::ApplicationSpecification()
{
}
