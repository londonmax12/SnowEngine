#include "snowpch.h"
#include "Application.h"

Snow::Application::Application(ApplicationSpecification spec)
{
	WindowSpecification windowSpec{spec.Name, spec.WindowWidth, spec.WindowHeight};
	windowSpec.x = spec.WindowX;
	windowSpec.y = spec.WindowY;
	m_Window = new Window(windowSpec, &m_State);
}

Snow::Application::~Application()
{
}

void Snow::Application::Run()
{
	SNOW_FATAL("Test %f", 3.45f);
	SNOW_ERROR("Test %f", 3.45f);
	SNOW_WARN("Test %f", 3.45f);
	SNOW_INFO("Test %f", 3.45f);
	SNOW_TRACE("Test %f", 3.45f);
	SNOW_DEBUG("Test %f", 3.45f);
	while (m_Running) {

	}
}

Snow::ApplicationSpecification::ApplicationSpecification()
{
}
