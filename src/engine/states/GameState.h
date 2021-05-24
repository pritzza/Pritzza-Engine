#pragma once

#include "State.h"

#include "../game objects/Entity.h"

#include "../levels/TileMap.h"

#include "../gfx/Text.h"

#include "SFML/Audio.hpp"

class GameState : public State
{
private:

	//sf::Image buffer;
	//
	//sf::Texture t;
	//Sprite s;

	sf::Sound bgm;

	Text text;

	bool isZoomedIn{ false };

	float time{};

	int p{};

	TileMap tileMap;
	
	std::shared_ptr<Entity> e1 = std::make_shared<Entity>();
	std::shared_ptr<Entity> e2 = std::make_shared<Entity>();
	
	std::vector<std::shared_ptr<Entity>> entities;

public:
	GameState(GameData& data) : State{ data } {}

	void virtual load();
	void virtual unload();

	void virtual handleInput();		// makes events based on keyboard input
	void virtual update(const double dt, const double pt = 0);	// updates all objects of state
	void virtual render() const;
};