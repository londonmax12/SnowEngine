#pragma once
#include "src/Platform/Platform.h"
#include "src/Event/Event.h"
#include "src/Application/Base.h"
namespace Snow {
	struct WindowSpecification {
		const char* windowName;
		int x = 0;
		int y = 0;
		int width;
		int height;

		WindowSpecification(const char* name, int w, int h)
			: windowName(name), width(w), height(h) {}
	};

	class Window {
	public:
		Window() = default;
		Window(WindowSpecification spec, PlatformState* state);
		~Window();
		bool Init(PlatformState* platformState);
		bool WantClose() { return m_WantClose; };

		static inline PlatformState* m_PlatformState;

	protected:
		const char* m_ApplicationName;
		int m_X;
		int m_Y;
		int m_Width;
		int m_Height;
		bool m_WantClose = false;
	};
}