#include "Mouse.h"

#include <SFML/Window.hpp>

Mouse::Mouse(sf::Window& window)
	:
	window{ window }
{
}

void Mouse::update()
{
	rclick.update(sf::Mouse::isButtonPressed(sf::Mouse::Left));
	lclick.update(sf::Mouse::isButtonPressed(sf::Mouse::Right));
	mclick.update(sf::Mouse::isButtonPressed(sf::Mouse::Middle));
}

const sf::Vector2i& Mouse::getPos() const
{
	return sf::Mouse::getPosition(this->window);
}
