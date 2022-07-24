#pragma once
#include "src/Platform/Platform.h"
#include "src/Time/DeltaTime.h"

namespace Snow {
	enum RendererType {
		RENDER_TYPE_VULKAN
	};

	class RendererBackend 
	{
	public:
		virtual bool Init(const char* applicationName, PlatformState* m_PlatformState) = 0;
		virtual void Shutdown() = 0;
		virtual void Resized(int width, int height) = 0;

		virtual bool BeginFrame(DeltaTime dt) = 0;
		virtual bool EndFrame(DeltaTime dt) = 0;

	private:
		PlatformState* m_PlatformState;
	};

	struct RenderCommand
	{
		DeltaTime deltaTime;
	};
}