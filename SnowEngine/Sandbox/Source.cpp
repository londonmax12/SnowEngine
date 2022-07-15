#include "src/Application/EntryPoint.h"

Snow::Application* Snow::CreateApplication()
{
	return new Application(ApplicationSpecification());
}