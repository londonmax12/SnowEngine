#include "snowpch.h"
#include "Application.h"

Snow::Application::Application(ApplicationSpecification spec)
{
}

Snow::Application::~Application()
{
}

void Snow::Application::Run()
{
	SNOW_INFO("Test %f", 3.45f);
}

Snow::ApplicationSpecification::ApplicationSpecification()
{
}
