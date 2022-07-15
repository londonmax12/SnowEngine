#pragma once

#include "Application.h"

extern Snow::Application* Snow::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Snow::CreateApplication();
	app->Run();
	delete app;
}