#pragma once

#include "Button.h"

namespace sf { class RenderWindow; }

class Keyboard
{
private:
	sf::RenderWindow& window;

public:
	Button w, a, s, d;

public:
	Keyboard(sf::RenderWindow& window);

	void update();
};