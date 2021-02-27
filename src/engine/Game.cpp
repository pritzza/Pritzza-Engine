#include "Game.h"

#include "states/GameState.h"

Game::Game(const std::string& windowName, const unsigned int windowWidth, const unsigned int windowHeight, const unsigned int windowScale, const unsigned int frameRate)
	:
	FRAME_RATE{frameRate},
	data{windowName, windowWidth, windowHeight, windowScale}
{
	// add starting state
	data.stateMachine.queueOperation({ STATE_MACHINE_OPERATION::ADD, STATE_ID::DEFAULT, std::make_shared<GameState>(GameState(data)) });
	// change to said state
	data.stateMachine.queueOperation({ STATE_MACHINE_OPERATION::CHANGE, STATE_ID::DEFAULT });
}

void Game::gameLoop()
{
	float dt{};

	while (isRunning())
	{
		clock.restart();	

		data.stateMachine.processChanges();
		data.window.update();

		if (data.window.isFocused() && data.stateMachine.currentState() != nullptr)
		{
			if (!data.stateMachine.currentState()->isLoaded())
				data.stateMachine.currentState()->load();

			data.stateMachine.currentState()->handleInput();
			data.stateMachine.currentState()->update(dt);
			data.stateMachine.currentState()->render();
		}

		dt = clock.getElapsedTime().asSeconds();	// processing time before wait
		sf::sleep(sf::seconds(1.f / FRAME_RATE - dt));

		dt = clock.getElapsedTime().asSeconds();	// total time (use this for dt calculations)
	}
}

bool Game::isRunning() const
{
	return data.window.isOpen();
}