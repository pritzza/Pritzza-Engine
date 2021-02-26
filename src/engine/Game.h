#pragma once

#include "util/GameData.h"

class Game
{
private:
	GameData data;

	sf::Clock clock;
	const unsigned int FRAME_RATE;

private:
	bool isRunning() const;

public:
	Game(const std::string& windowName, const unsigned int windowWidth, const unsigned int windowHeight, const unsigned int windowScale, const unsigned int frameRate);

	void gameLoop();
};