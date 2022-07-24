#include "snowpch.h"
#include "Renderer.h"

bool Snow::Renderer::Init(const char* appName, PlatformState* state)
{
	m_Backend = CreateBackend(RENDER_TYPE_VULKAN);

	if (!m_Backend->Init(appName, state)) {
		SNOW_FATAL("Failed to init renderer backend");
		return false;
	}
	return true;
}

void Snow::Renderer::Shutdown()
{
	m_Backend->Shutdown();
	delete m_Backend;
}

bool Snow::Renderer::DrawFrame(RenderCommand* command)
{
	if (m_Backend->BeginFrame(command->deltaTime)) {
		bool result = m_Backend->EndFrame(command->deltaTime);

		if (!result) {
			SNOW_FATAL("Renderer failed to end frame");
			return false;
		}
	}
	return true;
}


