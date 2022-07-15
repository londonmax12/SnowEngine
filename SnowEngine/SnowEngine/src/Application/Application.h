#pragma once

#include <string>

#include "../Window/Window.h"

namespace Snow {
	struct ApplicationSpecification {
		const char* Name = "Snow Application";
		//bool InitRenderer = true;

		int WindowX = 100;
		int WindowY = 100;
		int WindowWidth = 1600;
		int WindowHeight = 900;

		bool WindowDecorated = true;

		ApplicationSpecification();
		ApplicationSpecification(const char* name,
			int windowWidth = 1600,
			int windowHeight = 900)
			: Name(name), WindowWidth(windowWidth), WindowHeight(windowHeight) {}
	};

	class Application
	{
	public:
		Application(ApplicationSpecification spec);
		~Application();

		void Run();
	private:
		bool m_Running = true;

		Window* m_Window;
		PlatformState m_State;
	};

	Application* CreateApplication();
}