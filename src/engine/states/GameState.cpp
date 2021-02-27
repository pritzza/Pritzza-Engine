#include "GameState.h"

#include "../util/GameData.h"

#include <iostream>

void GameState::load()
{
	std::cout << "load GAMESTATE\n";
	// load all resources

	auto& tm = data.resourceManagers.textureManager;

	tm.load(TEXTURE::DEFAULT);
	s.setTexture(tm.get(TEXTURE::DEFAULT));	// s is sf::Sprite

	setLoaded();
}

void GameState::unload()
{
	std::cout << "unload GAMESTATE\n";
	// release all resources

	data.resourceManagers.textureManager.unload(TEXTURE::DEFAULT);
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

	data.window.draw(s);
	// render scene objects and entities and stuff here

	data.window.endDraw();
}
