#pragma once

#include "State.h"

#include <SFML/Graphics.hpp>

#include <vector>

class GameState : public State
{
private:
	sf::Sprite s1;
	sf::Sprite s2;

	std::vector<sf::Sprite*> sprites;

public:
	GameState(GameData& data) : State{ data } { std::cout << "GAMESTATE constructor"; }

	void virtual load();
	void virtual unload();

	void virtual handleInput();		// makes events based on keyboard input
	void virtual update(const float dt);	// updates all objects of state
	void virtual render() const;
};