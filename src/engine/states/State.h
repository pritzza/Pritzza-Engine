#pragma once

struct GameData;

#include <iostream>

class State
{
private:
	bool loaded{ false };	// have its resources been loaded

protected:
	GameData& data;

protected:
	void setLoaded() { this->loaded = true; }

public:
	State(GameData& data) : data{ data } { std::cout << "STATE constructor\n"; }
	virtual ~State() { std::cout << "STATE deconstructor\n"; unload(); }

	void virtual load() = 0;
	void virtual unload() {}

	void virtual handleInput() = 0;		// makes events based on keyboard input
	void virtual update(const float dt) = 0;	// updates all objects of state
	void virtual render() const = 0;

	const bool isLoaded() const { return this->loaded; }
};