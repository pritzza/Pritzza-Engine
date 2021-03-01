#include "GameState.h"

#include "../util/GameData.h"

#include <iostream>

void GameState::load()
{
	std::cout << "load GAMESTATE\n";
	// load all resources

	auto& tm = data.resourceManagers.textureManager;

	//tm.load(TEXTURE::DEFAULT);
	s1.setTexture(tm.get(TEXTURE::ERROR));
	s2.setTexture(tm.get(TEXTURE::ERROR));

	sprites.push_back(&s1);
	sprites.push_back(&s2);

	s1.setPosition(100, 10);

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

	for (const auto s : sprites)
		data.window.draw(*s);
	// render scene objects and entities and stuff here

	data.window.endDraw();
}
