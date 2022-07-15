#include "snowpch.h"
#include "Application.h"
#include "../Memory/Memory.h"

Snow::Application::Application(ApplicationSpecification spec)
{
	WindowSpecification windowSpec{spec.Name, spec.WindowWidth, spec.WindowHeight};
	windowSpec.x = spec.WindowX;
	windowSpec.y = spec.WindowY;
	SNOW_INFO("Creating window (%s): %i, %i", spec.Name, spec.WindowWidth, spec.WindowHeight);

	m_Window = new Window(windowSpec, &m_State);

	Memory::MemInit();
}

Snow::Application::~Application()
{
	delete m_Window;
	Memory::MemShutdown();
}

void Snow::Application::Run()
{
	while (m_Running) {
		if (!platform_PumpMessages(&m_State)) {
			m_Running = false;
		}
	}
}

Snow::ApplicationSpecification::ApplicationSpecification()
{
}
