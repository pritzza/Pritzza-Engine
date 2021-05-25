#pragma once

#include "Button.h"

#include "SFML/System/Vector2.hpp"

namespace sf { class Window; }

class Mouse
{
private:
	sf::Window& window;

public:
	Button lclick, rclick, mclick;

public:
	Mouse(sf::Window& window);

	void update();

	const sf::Vector2i& getPos() const;
};