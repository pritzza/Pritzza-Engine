#pragma once

#include "State.h"

#include "../game objects/Entity.h"

#include "../levels/TileMap.h"

class GameState : public State
{
private:

	//sf::Image buffer;
	//
	//sf::Texture t;
	//Sprite s;
	
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
	void virtual update(const float dt);	// updates all objects of state
	void virtual render() const;
};