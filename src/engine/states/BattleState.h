#pragma once

#include "State.h"

#include "../game objects/Entity.h"

#include "../levels/TileMap.h"

#include "../gfx/Text.h"

#include "SFML/Audio.hpp"

class BattleState : public State
{
private:
	static constexpr int MIN_LEN{ 75 };
	static constexpr int HOUR_LEN{ 50 };

	static constexpr float MAX_CLOCK_DISTANCE{ .1f };

private:
	Text clockDistanceText;
	Text scoreText;

	bool hit{ false };
	bool passedClockMax{ true };

	double clockTime{};
	float clockSpeed{};
	float distance{};

	int points{};

	double time{};

	sf::Sound hitSound;

	sf::Vertex minuteHand[2];
	sf::Vertex hourHand[2];

public:
	BattleState(GameData& data) : State{ data } {}

	void virtual load();
	void virtual unload();

	void virtual handleInput();		// makes events based on keyboard input
	void virtual update(const double dt, const double pt = 0);	// updates all objects of state
	void virtual render() const;
};