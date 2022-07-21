#include "SnowEngine.h"

class Sandbox : public Snow::Application {
public:
	Sandbox(Snow::ApplicationSpecification spec) 
		:Snow::Application(spec)
	{

	}
	void OnUpdate(Snow::DeltaTime dt) {
		if (Snow::Input::IsKeyPressed(Snow::Key::W))
			SNOW_TRACE("Button 0 pressed");
	}
};

Snow::Application* Snow::CreateApplication()
{
	return new Sandbox(ApplicationSpecification("Sandbox"));
}