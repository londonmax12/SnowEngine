#pragma once
#include "snowpch.h"

#include "../Window/Window.h"
#include "../Time/DeltaTime.h"
#include "../Event/MouseEvent.h"
#include "../Event/ApplicationEvent.h"

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

		virtual void OnUpdate(DeltaTime dt) = 0;

		void OnEvent(Event& e);
		bool OnWindowClose(Event& e);
		bool OnWindowResized(Event& e);

		static Application* GetInstance() { return m_Instance; };
	private:
		bool m_Running = true;

		Window* m_Window;
		PlatformState m_State;

		static inline Application* m_Instance;
	};

	Application* CreateApplication();
}