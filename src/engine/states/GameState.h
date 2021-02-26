#pragma once

#include "State.h"

class GameState : public State
{
public:
	GameState(GameData& data) : State(data) {}
	virtual ~GameState() override;

	void virtual load();

	void virtual handleInput();		// makes events based on keyboard input
	void virtual update(const float dt);	// updates all objects of state
	void virtual render() const;
};