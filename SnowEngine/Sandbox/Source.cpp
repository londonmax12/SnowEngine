#include "SnowEngine.h"

class Sandbox : public Snow::Application {
public:
	Sandbox(Snow::ApplicationSpecification spec) 
		:Snow::Application(spec)
	{

	}
};

Snow::Application* Snow::CreateApplication()
{
	return new Sandbox(ApplicationSpecification("Sandbox"));
}