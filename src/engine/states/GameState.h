#pragma once

#include "State.h"

#include "../game objects/Entity.h"

#include "../levels/TileMap.h"

class GameState : public State
{
private:
	TileMap tileMap;

	Entity e1;
	Entity e2;

	std::vector<Entity*> entities;

public:
	GameState(GameData& data) : State{ data } {}

	void virtual load();
	void virtual unload();

	void virtual handleInput();		// makes events based on keyboard input
	void virtual update(const float dt);	// updates all objects of state
	void virtual render() const;
};