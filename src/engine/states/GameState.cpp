#include "GameState.h"

#include "../util/GameData.h"

GameState::~GameState()
{
	// release all resources
}

void GameState::load()
{
	// load all resources
}

void GameState::handleInput()
{
	// listen to any keyboard and mouse input to do stuff
}

void GameState::update(const float dt)
{
	// tick everything
}

void GameState::render() const
{
	data.window.beginDraw();

	// render scene objects and entities and stuff here

	data.window.endDraw();
}
