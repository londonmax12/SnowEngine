#include "snowpch.h"
#include "src/Event/Input.h"

bool Snow::Input::IsKeyPressed(KeyCode key)
{
    return GetKeyState(key) < 0;
}

bool Snow::Input::IsMouseButtonPressed(MouseCode button)
{
    return GetKeyState(button) < 0;
}

std::pair<int, int> Snow::Input::GetMousePosition()
{
    POINT p;
    GetCursorPos(&p);
    return std::pair<int, int>(p.x, p.y);
}

float Snow::Input::GetMouseX()
{
    POINT p;
    GetCursorPos(&p);
    return p.x;
}

float Snow::Input::GetMouseY()
{
    POINT p;
    GetCursorPos(&p);
    return p.y;
}
