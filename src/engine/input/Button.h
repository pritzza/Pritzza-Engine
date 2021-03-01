#pragma once

enum class BUTTON_STATE
{
	TAPPED,
	HELD,
	RELEASED,
	IDLE
};

class Button
{
private:
	BUTTON_STATE state;

public:
	void update(const bool isPressed);

	const bool isTapped() const;
	const bool isHeld() const;
	const bool isReleased() const;
	const bool isIdle() const;
};