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

// once you reach the last frame of an animation cycle, you go back to the first frame, instead of backwards from the last
enum class AnimationCycleType
{
	JUMP_BACK,
	OSCILLATING
};

// whether you're going forward or backwards in the animation frame indexes during AnimationCycleType::OSCILLATING
enum class OscillationalDirection
{
	FORWARD,
	BACKWARD
};

class AnimatedSprite : public Sprite
{
private:
	bool isAnimated{ false };	// animated sprites will be un animated by default such that game objects can have AnimatedSprite objects but not be animated

	sf::Vector2i currentSpriteTile;
	sf::Vector2i spriteSheetTileDimensions;

	float frameDuration;
	float frameCounter;

	AnimationState animationState;

	AnimationCycleType animationCycleType{ AnimationCycleType::JUMP_BACK };
	OscillationalDirection oscillationalDirection{ OscillationalDirection::FORWARD };

private:
	void updateCrop();
	void updateFrame(const float dt);
	void updateAnimationState(const Direction& dir, const bool isMoving);

	// two different styles of looping through animation frames
	void updateFrameJumpingBack();
	void updateFrameOscillating();

public:
	AnimatedSprite() {};
	AnimatedSprite(const sf::Vector2f& pos, const sf::Vector2i& dimensions, const sf::Texture& texture);
	AnimatedSprite(const sf::Vector2f& pos, const sf::Vector2i& dimensions, const sf::Texture& texture, const sf::Vector2i shDimensions, const float maxFrameDur);

	virtual void update(const sf::Vector2f& pos, const float dt, const Direction& dir, const bool isMoving);	// remember to always pass in dt

	void setAnimationState(const AnimationState state);
	void setSpriteSheetDimensions(const sf::Vector2i dimensions);
	void setKeyFrameMaxDuration(const float duration);
	void setAnimationCycleType(const AnimationCycleType type);

	// IMPORTANT! be sure to set to true if using an animated sprite
	void setIsAnimated(const bool isAnimated);

	const AnimationState getAnimationState() const;
};