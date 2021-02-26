#pragma once

class GameData;

class State
{
protected:
	GameData& data;
	bool loaded{ false };	// have its resources been loaded

public:
	State(GameData& data) : data{ data } {}
	virtual ~State() {}

	void virtual load() = 0;

	void virtual handleInput() = 0;		// makes events based on keyboard input
	void virtual update(const float dt) = 0;	// updates all objects of state
	void virtual render() const = 0;

	const bool isLoaded() const { return this->loaded; }
};