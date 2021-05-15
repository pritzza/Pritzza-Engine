#pragma once

#include "Sprite.h"

enum class AnimationState
{
	IDLE_UP,
	IDLE_LEFT,
	IDLE_RIGHT,
	IDLE_DOWN,

	MOVING_UP,
	MOVING_LEFT,
	MOVING_RIGHT,
	MOVING_DOWN,

	NUM_ANIMATIONS
};

class AnimatedSprite : public Sprite
{
private:
	bool isAnimated{ false };	// animated sprites will be un animated by default such that game objects can have AnimatedSprite objects but not be animated

	sf::Vector2u currentSpriteTile;
	sf::Vector2u spriteSheetTileDimensions;

	float keyFrameMaxDuration;
	float keyFrameCounter;

	AnimationState animationState;

	bool isSnapBackAnimation{ true };	// once you reach the last frame of an animation cycle, you go back to the first frame, instead of backwards from the last
	bool isFrameDirectionForward{ false };	// used to go backwards when !isSnapBackAnimation

private:
	void updateCrop();
	void updateFrame(const float dt);
	void updateAnimationState(const Direction& dir, const bool isMoving);

public:
	AnimatedSprite() {};
	AnimatedSprite(const sf::Vector2f& pos, const sf::Vector2u& dimensions, const sf::Texture& texture);
	AnimatedSprite(const sf::Vector2f& pos, const sf::Vector2u& dimensions, const sf::Texture& texture, const sf::Vector2u shDimensions, const float maxFrameDur);

	virtual void update(const sf::Vector2f& pos, const float dt, const Direction& dir, const bool isMoving);	// remember to always pass in dt

	void setAnimationState(const AnimationState state);
	void setSpriteSheetDimensions(const sf::Vector2u dimensions);
	void setKeyFrameMaxDuration(const float duration);
	void setIsAnimated(const bool isAnimated);

	const AnimationState getAnimationState() const;
};