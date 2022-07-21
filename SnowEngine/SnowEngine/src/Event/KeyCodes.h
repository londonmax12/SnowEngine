#pragma once

#include "snowpch.h"

namespace Snow {
	using KeyCode = uint16_t;

	namespace Key
	{
		enum : KeyCode
		{
			Space = VK_SPACE,
			Comma = VK_OEM_COMMA, /* , */
			Minus = VK_OEM_MINUS, /* - */
			Period = VK_OEM_PERIOD, /* . */

			D0 = 48, /* 0 */
			D1 = 49, /* 1 */
			D2 = 50, /* 2 */
			D3 = 51, /* 3 */
			D4 = 52, /* 4 */
			D5 = 53, /* 5 */
			D6 = 54, /* 6 */
			D7 = 55, /* 7 */
			D8 = 56, /* 8 */
			D9 = 57, /* 9 */

			Equal = VK_OEM_NEC_EQUAL, /* = */

			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,

			LeftBracket = 0xDB,  /* [ */
			Backslash = 0xC0,  /* \ */
			RightBracket = 0xDD,  /* ] */
			GraveAccent = 0xC0,  /* ` */

			/* Function keys */
			Escape = VK_ESCAPE,
			Enter = 13,
			Tab = VK_TAB,
			Backspace = VK_BACK,
			Insert = VK_INSERT,
			Delete = VK_DELETE,
			Right = VK_RIGHT,
			Left = VK_LEFT,
			Down = VK_DOWN,
			Up = VK_UP,
			PageUp = VK_PRIOR,
			PageDown = VK_NEXT,
			Home = VK_HOME,
			End = VK_END,
			CapsLock = VK_CAPITAL,
			ScrollLock = VK_SCROLL,
			NumLock = VK_NUMLOCK,
			PrintScreen = VK_PRINT,
			Pause = VK_PAUSE,
			F1 = VK_F1,
			F2 = VK_F2,
			F3 = VK_F3,
			F4 = VK_F4,
			F5 = VK_F5,
			F6 = VK_F6,
			F7 = VK_F7,
			F8 = VK_F8,
			F9 = VK_F9,
			F10 = VK_F10,
			F11 = VK_F11,
			F12 = VK_F12,
			F13 = VK_F13,
			F14 = VK_F14,
			F15 = VK_F15,
			F16 = VK_F16,
			F17 = VK_F17,
			F18 = VK_F18,
			F19 = VK_F19,
			F20 = VK_F20,
			F21 = VK_F21,
			F22 = VK_F22,
			F23 = VK_F23,
			F24 = VK_F24,

			/* Keypad */
			KP0 = VK_NUMPAD0,
			KP1 = VK_NUMPAD1,
			KP2 = VK_NUMPAD2,
			KP3 = VK_NUMPAD3,
			KP4 = VK_NUMPAD4,
			KP5 = VK_NUMPAD5,
			KP6 = VK_NUMPAD6,
			KP7 = VK_NUMPAD7,
			KP8 = VK_NUMPAD8,
			KP9 = VK_NUMPAD9,

			LeftShift = VK_LSHIFT,
			LeftControl = VK_LCONTROL,
			LeftAlt = VK_LMENU,
			LeftSuper = VK_LWIN,
			RightShift = VK_RSHIFT,
			RightControl = VK_RCONTROL,
			RightAlt = VK_RMENU,
			RightSuper = VK_RWIN,
			Menu = VK_MENU
		};
	}
}