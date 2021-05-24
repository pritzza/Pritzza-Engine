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
	double dt{};	// delta time; time between each frame
	double pt{};	// processing time; it it takes to execute one gameloop

	while (isRunning())
	{
		frameTimer.restart();	

		data.stateMachine.processChanges();

		data.window.update();

		if (data.window.isFocused() && data.stateMachine.currentState() != nullptr)
		{
			data.camera.update(dt);

			//data.mouse.update();
			data.keyboard.update();

			if (!data.stateMachine.currentState()->isLoaded())
			{
				data.stateMachine.currentState()->load();
				continue;
			}

			data.stateMachine.currentState()->handleInput();
			data.stateMachine.currentState()->update(dt, pt);
			data.stateMachine.currentState()->render();
		}

		pt = frameTimer.getElapsedTime().asSeconds();	// processing time before wait
		sf::sleep(sf::seconds(1.f / FRAME_RATE - pt));

		dt = frameTimer.getElapsedTime().asSeconds();	// total time (use this for dt calculations)
	}
}

bool Game::isRunning() const
{
	return data.window.isOpen();
}