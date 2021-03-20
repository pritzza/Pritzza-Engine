#pragma once

#include "GameObject.h"

class Entity : public GameObject
{
private:
	sf::Vector2f vel;
	sf::Vector2f acc;

private:
	void updatePhysics(const float dt);
	void updatePos(const float dt);
	
public:
	virtual void init(const sf::Vector2f& pos, const sf::Vector2u& dimensions);

	virtual void update(const float dt);

	void move(const sf::Vector2f& v);

	const sf::Vector2f& getVel() const;
};