#pragma once

#include "Window.h"
#include "../states/StateMachine.h"
#include "../resource manager/ResourceManagers.h"

struct GameData
{
	GameData(const std::string& windowName, const unsigned int windowWidth, const unsigned int windowHeight, const unsigned int windowScale)
		:
		window{ windowName, windowWidth, windowHeight, windowScale }
	{}

	Window window;
	StateMachine stateMachine;
	ResourceManagers resourceManagers;
};