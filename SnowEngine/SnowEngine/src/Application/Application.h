#pragma once

#include <string>

namespace Snow {
	struct ApplicationSpecification {
		std::string Name = "Snow Application";
		bool InitRenderer = true;

		int WindowWidth = 1600;
		int WindowHeight = 900;

		bool WindowDecorated = true;

		ApplicationSpecification();
		ApplicationSpecification(std::string name,
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
	};

	Application* CreateApplication();
}