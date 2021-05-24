#pragma once

#include "GameObject.h"

#include "../util/Direction.h"

class Entity : public GameObject
{
private:
	static constexpr float MAX_VEL{ 120.0f };
	static constexpr float MIN_VEL{ 2.f };
	static constexpr float DECELERATION_RATE{ 6.f };

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
	// needs refactor
	virtual void init(const sf::Vector2f& pos, const sf::Vector2i& dimensions);
	virtual void init(const sf::Vector2f& pos, const sf::Vector2i& dimensions, const sf::Texture& t);
	virtual void init(const sf::Vector2f& pos, const sf::Vector2i& dimensions, const sf::Texture& t, const sf::Vector2i& shDimensions, const float maxFrameDur);

	virtual void update(const float dt);

	void move(const sf::Vector2f& v);

	void setAcceleration(const sf::Vector2f acc);

	const sf::Vector2f& getVel() const;
};