#pragma once

#include "State.h"

#include <SFML/Graphics.hpp>

class GameState : public State
{
private:
	sf::Texture t;
	sf::Sprite s;

public:
	GameState(GameData& data) : State{ data } {}

	void virtual load();
	void virtual unload();

	void virtual handleInput();		// makes events based on keyboard input
	void virtual update(const float dt);	// updates all objects of state
	void virtual render() const;
};