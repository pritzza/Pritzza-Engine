#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const sf::Vector2f& pos, const sf::Vector2i& dimensions, const sf::Texture& texture)
	:
	Sprite(pos, dimensions, texture)
{
}

AnimatedSprite::AnimatedSprite(const sf::Vector2f& pos, const sf::Vector2i& dim, const sf::Texture& t, const sf::Vector2i shDim, const float maxFrameDur)
	:
	Sprite(pos, dim, t)
{
	this->setSpriteSheetDimensions(shDim);
	this->setKeyFrameMaxDuration(maxFrameDur);
}

void AnimatedSprite::updateCrop()
{
	const int spriteW = this->sbox.width;
	const int spriteH = this->sbox.height;
	int curFrameX = this->currentSpriteTile.x;
	int curFrameY = this->currentSpriteTile.y;
	
	// if currentSpriteTile go out of bounds, set to 0
	if (curFrameX > spriteSheetTileDimensions.x || curFrameX < 0)
		curFrameX = 0;
	if (curFrameY > spriteSheetTileDimensions.y || curFrameY < 0)
		curFrameY = 0;

	this->sprite.setTextureRect( { (curFrameX * spriteW), (curFrameY * spriteH), spriteW, spriteH } );
}

void AnimatedSprite::updateFrame(const float dt)
{
	frameCounter += dt;

	if (frameCounter >= frameDuration)
	{
		frameCounter -= frameDuration;

		if (animationCycleType == AnimationCycleType::JUMP_BACK)
			this->updateFrameJumpingBack();
		else
			this->updateFrameOscillating();
	}
}

// logic for going from animation frame 0, 1, 2, ... n-2, n-1, n, 0, 1, 2
void AnimatedSprite::updateFrameJumpingBack()
{
	++currentSpriteTile.x;

	if (currentSpriteTile.x >= spriteSheetTileDimensions.x)
		currentSpriteTile.x %= spriteSheetTileDimensions.x;
}

// logic for going from animation frame 0, 1, 2, ... n-1, n, n-1, ... 2, 1, 0
void AnimatedSprite::updateFrameOscillating()
{
	if (currentSpriteTile.x >= spriteSheetTileDimensions.x - 1)
	{
		oscillationalDirection = OscillationalDirection::FORWARD;
	}
	else if (currentSpriteTile.x == 0)	// unsigned int < 0 doesnt exist because of integer underflow (must be == 0)
	{
		oscillationalDirection = OscillationalDirection::BACKWARD;
	}

	if (oscillationalDirection == OscillationalDirection::FORWARD)
		++currentSpriteTile.x;
	else
		--currentSpriteTile.x;
}

void AnimatedSprite::updateAnimationState(const Direction& dir, const bool isMoving)
{
	AnimationState state;

	if (isMoving)
		switch (dir)
		{
		case Direction::UP:		state = AnimationState::MOVING_UP;			break;
		case Direction::LEFT:	state = AnimationState::MOVING_LEFT;		break;
		case Direction::RIGHT:	state = AnimationState::MOVING_RIGHT;		break;
		case Direction::DOWN:	state = AnimationState::MOVING_DOWN;		break;
		}
	else	// if you're not moving anymore, play your idle animation
		switch (dir)
		{
		case Direction::UP:		state = AnimationState::IDLE_UP;			break;
		case Direction::LEFT:	state = AnimationState::IDLE_LEFT;			break;
		case Direction::RIGHT:	state = AnimationState::IDLE_RIGHT;			break;
		case Direction::DOWN:	state = AnimationState::IDLE_DOWN;			break;
		}

	this->setAnimationState(state);
}

void AnimatedSprite::update(const sf::Vector2f& pos, const float dt, const Direction& dir, const bool isMoving)
{
	this->setSpritePos(pos);

	// only call AnimatedSprite methods if it has been initialzied as a fully fledged AnimatedSprite (need to refactor)
	if (this->isAnimated)
	{
		this->updateAnimationState(dir, isMoving);
		this->updateFrame(dt);
		this->updateCrop();
	}
}

void AnimatedSprite::setAnimationState(const AnimationState state)			 { this->currentSpriteTile.y = static_cast<int>(state); }
void AnimatedSprite::setSpriteSheetDimensions(const sf::Vector2i dimensions) { this->spriteSheetTileDimensions = dimensions;		}
void AnimatedSprite::setKeyFrameMaxDuration(const float duration)			 { this->frameDuration = duration;						}
void AnimatedSprite::setAnimationCycleType(const AnimationCycleType type)	 { this->animationCycleType = type;						}
void AnimatedSprite::setIsAnimated(const bool isAnimated)					 { this->isAnimated = isAnimated;						}

const AnimationState AnimatedSprite::getAnimationState() const { return this-> animationState; }