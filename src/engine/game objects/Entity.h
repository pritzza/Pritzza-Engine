#pragma once

#include "GameObject.h"

#include "../util/Direction.h"

class Entity : public GameObject
{
private:
	sf::Vector2f vel;
	sf::Vector2f acc;

	bool isMoving;

	Direction direction;

private:
	void updatePhysics(const float dt);
	void updatePos(const float dt);
	void updateDirection(const sf::Vector2f& v);

public:
	virtual void init(const sf::Vector2f& pos, const sf::Vector2u& dimensions);
	virtual void init(const sf::Vector2f& pos, const sf::Vector2u& dimensions, const sf::Texture& t);
	virtual void init(const sf::Vector2f& pos, const sf::Vector2u& dimensions, const sf::Texture& t, const sf::Vector2u& shDimensions, const float maxFrameDur);

	virtual void update(const float dt);

	void move(const sf::Vector2f& v);

	const sf::Vector2f& getVel() const;
};