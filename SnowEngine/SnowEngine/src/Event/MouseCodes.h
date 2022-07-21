#pragma once

#include "snowpch.h"

namespace Snow {
	using Mousecode = uint16_t;
	enum MouseCode
	{
		Button0 = VK_LBUTTON,
		Button1 = VK_RBUTTON,
		Button2 = VK_MBUTTON,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	};

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}