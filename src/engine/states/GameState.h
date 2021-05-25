#pragma once

#include "State.h"

#include "../game objects/Entity.h"

#include "../levels/TileMap.h"

#include "../gfx/Text.h"

class GameState : public State
{
private:
	static constexpr int LEVEL_WIDTH{ 250 };
	static constexpr int LEVEL_HEIGHT{ 250 };

private:
	std::vector<std::shared_ptr<Entity>> entities;

	std::shared_ptr<Entity> e1 = std::make_shared<Entity>();
	std::shared_ptr<Entity> e2 = std::make_shared<Entity>();

	TileMap tileMap;

	bool isZoomedIn{ false };

	float time{};
	
	Text text;

public:
	GameState(GameData& data) : State{ data } {}

	void virtual load();
	void virtual unload();

	void virtual handleInput();		// makes events based on keyboard input
	void virtual update(const double dt, const double pt = 0);	// updates all objects of state
	void virtual render() const;
};