#pragma once

#include "Sprite.h"

class AnimatedSprite : public Sprite
{
public:
	void update(const sf::Vector2f& pos, const float dt = 0.f);	// remember to always pass in dt
};