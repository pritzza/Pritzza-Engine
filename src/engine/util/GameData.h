#pragma once

#include "Window.h"

#include "../states/StateMachine.h"

#include "../resource manager/ResourceManagers.h"

#include "../gfx/Camera.h"

#include "../input/Keyboard.h"
#include "../input/Mouse.h"

struct GameData
{
	GameData(const std::string& windowName, const unsigned int windowWidth, const unsigned int windowHeight, const unsigned int windowScale)
		:
		window { camera, windowName, windowWidth, windowHeight, windowScale },
		camera { windowWidth, windowHeight },
		keyboard { window.getWindow() },
		mouse { window.getWindow() }
	{}

	Camera camera;
	Window window;
	
	StateMachine stateMachine;
	ResourceManagers resourceManagers;
	
	Keyboard keyboard;
	Mouse mouse;

};