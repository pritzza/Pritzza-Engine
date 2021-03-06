#pragma once

#include <SFML/Graphics.hpp>

class AABB
{
private:
	sf::IntRect cbox;
	sf::RectangleShape rect;

private:
	void setRectPos(const sf::Vector2f& p);

public:
	AABB();

	void update(const sf::Vector2f& pos);

	bool isColliding(const AABB& target) const;

	void setDimensions(const sf::Vector2u dimensions);

	const sf::Vector2f& getPos() const;
	const sf::IntRect& getBox() const;

	const sf::RectangleShape getRect() const;
};