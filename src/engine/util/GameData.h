#pragma once

#include "Window.h"
#include "../states/StateMachine.h"

class GameData
{
public:
	GameData(const std::string& windowName, const unsigned int windowWidth, const unsigned int windowHeight, const unsigned int windowScale)
		:
		window{ windowName, windowWidth, windowHeight, windowScale }
	{}

	Window window;
	StateMachine stateMachine;
};