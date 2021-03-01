#pragma once

#include "Window.h"
#include "../states/StateMachine.h"
#include "../resource manager/ResourceManagers.h"
#include "../gfx/Camera.h"

struct GameData
{
	GameData(const std::string& windowName, const unsigned int windowWidth, const unsigned int windowHeight, const unsigned int windowScale)
		:
		window { camera, windowName, windowWidth, windowHeight, windowScale },
		camera { windowWidth, windowHeight }
	{}

	Camera camera;
	Window window;
	
	StateMachine stateMachine;
	ResourceManagers resourceManagers;
	
};