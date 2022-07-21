#pragma once
#include "MouseCodes.h"
#include "KeyCodes.h"

#include "snowpch.h"

namespace Snow {
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);

		static std::pair<int, int> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

		virtual ~Input() = default;
	protected:
		Input() = default;
	private:
		static Input* s_Instance;
	};
}