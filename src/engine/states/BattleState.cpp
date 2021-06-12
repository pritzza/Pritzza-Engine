#include "BattleState.h"

#include "../util/GameData.h"

#include "GameState.h"

#include <iostream>

#include <cmath>

void BattleState::load()
{
	// load all resources

	//// LOADING RESOURCES

	// LOADING TEXTURES

	// LOADING AUDIO

	auto& sm = data.resourceManagers.soundManager;

	sm.load(SOUND::HIT);

	// LOAD TEXT

	auto& fm = data.resourceManagers.fontManager;

	//// INITIALIZING MEMBERS

	this->clockSpeed = .5f;

	// INITIALIZEING MAP

	// INITIALIZING ENTITIES

	// INITIALIZING CAMERA

	// INITIALIZING AUDIO

	this->hitSound.setBuffer(sm.get(SOUND::HIT));

	// INITIALIZING TEXT

	clockDistanceText.init(fm.get(FONT::ERROR), TextType::STATIC, "BATTLE STATE", { 69,69 }, 69);
	scoreText.init(fm.get(FONT::DEFAULT), TextType::STATIC, "score", { 100,100 }, 100);

	// INITIALIZING MISC

	minuteHand[0].position = { 0, 0 };
	minuteHand[1].position = { 0, MIN_LEN };
	hourHand[0].position =   { 0, 0 };
	hourHand[1].position =   { 0, HOUR_LEN };

	// FINISHING
	setLoaded();	// enable the state's "loaded" flag after everything has been loaded
}

void BattleState::unload()
{
	// release all resources
	// textures
	auto& tm = data.resourceManagers.textureManager;

	// fonts
	auto& fm = data.resourceManagers.fontManager;

	//fm.unload(FONT::);

	// audio
	//auto& am = data.resourceManagers.audioManager;

}

void BattleState::handleInput()
{
	// listen to any keyboard and mouse input to do stuff

	Keyboard& kb{ data.keyboard };

	if (data.mouse.rclick.isTapped())
	{
		if (this->distance < MAX_CLOCK_DISTANCE)
		{
			this->hitSound.play();
			this->points++;
			this->clockSpeed++;

			this->scoreText.setString(std::to_string(this->distance) + '\n' + std::to_string(points));
			this->scoreText.setFillColor(sf::Color::Black);
		}
		else
		{
			this->scoreText.setString(std::to_string(this->distance) + '\n' + std::to_string(points));
			this->scoreText.setFillColor(sf::Color::Red);

			this->points = 0;
			this->clockSpeed = 2;
		}
	}

	if (data.mouse.mclick.isTapped())
	{
		if (!data.stateMachine.isStateLoaded(STATE_ID::DEFAULT))
			data.stateMachine.queueOperation({ STATE_MACHINE_OPERATION::ADD, STATE_ID::DEFAULT, std::make_shared<GameState>(GameState(data)) });

		data.stateMachine.queueOperation({ STATE_MACHINE_OPERATION::CHANGE, STATE_ID::DEFAULT });
	}
}

void BattleState::update(const double dt, const double pt)
{
	time += dt;

	clockTime += dt * clockSpeed;

	minuteHand[1].position = { 
		cosf(clockTime) * MIN_LEN, 
		sinf(clockTime) * MIN_LEN 
	};

	const int hourDuration{ 8 };

	hourHand[1].position = { 
		cosf( (clockTime) / hourDuration ) * HOUR_LEN, 
		sinf( (clockTime) / hourDuration ) * HOUR_LEN 
	};

	const sf::Vector2i handDifference(
		minuteHand[1].position.x - hourHand[1].position.x,
		minuteHand[1].position.y - hourHand[1].position.y
	);

	distance = ( (std::hypotf(handDifference.x, handDifference.y) - (MIN_LEN - HOUR_LEN) ) / HOUR_LEN);

	if (!passedClockMax)
	{
		if (distance > MAX_CLOCK_DISTANCE)
			passedClockMax = true;
	}
	
	if (passedClockMax)
	{
		if (hit)
			hit = false;
	}

	clockDistanceText.setString("d:" + std::to_string(distance));

	//for (const auto e : entities)
	//	e->update(dt);
}

void BattleState::render() const
{
	// render scene objects and entities and stuff here

	Window& w{ data.window };

	w.beginDraw();

	w.getWindow().draw(minuteHand, 2, sf::Lines);
	w.getWindow().draw(hourHand, 2, sf::Lines);

	w.draw(clockDistanceText);
	w.draw(scoreText);

	w.endDraw();
}
