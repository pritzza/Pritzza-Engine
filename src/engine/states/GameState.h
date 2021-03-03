#pragma once

#include "State.h"

#include <SFML/Graphics.hpp>

#include "../entities/Entity.h"

#include <vector>

class GameState : public State
{
private:
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