#include "AnimatedSprite.h"

#include <iostream>

#include "../util/Direction.h"

AnimatedSprite::AnimatedSprite(const sf::Vector2f& pos, const sf::Vector2u& dimensions, const sf::Texture& texture)
	:
	Sprite(pos, dimensions, texture)
{
}

AnimatedSprite::AnimatedSprite(
	const sf::Vector2f& pos, 
	const sf::Vector2u& dimensions, 
	const sf::Texture& texture, 
	const sf::Vector2u shDimensions, 
	const float maxFrameDur)
	:
	Sprite(pos, dimensions, texture)
{
	this->setSpriteSheetDimensions(shDimensions);
	this->setKeyFrameMaxDuration(maxFrameDur);
}

void AnimatedSprite::updateCrop()
{
	int w = this->sbox.width;
	int h = this->sbox.height;
	int x = this->currentSpriteTile.x;
	int y = this->currentSpriteTile.y;
	
	// if currentSpriteTile go out of bounds, set to 0
	if (x > spriteSheetTileDimensions.x || x < 0)
		x = 0;
	if (y > spriteSheetTileDimensions.y || y < 0)
		y = 0;

	this->s.setTextureRect( { (x * w), (y * w), w, h } );
}

void AnimatedSprite::updateFrame(const float dt)
{
	keyFrameCounter += dt;

	if (keyFrameCounter >= keyFrameMaxDuration)
	{
		keyFrameCounter = 0.f;

		if (isSnapBackAnimation)
		{
			// logic for going from animation frame 0, 1, 2, ... n-2, n-1, n, 0, 1, 2
			++currentSpriteTile.x;

			if (currentSpriteTile.x >= spriteSheetTileDimensions.x)
				currentSpriteTile.x %= spriteSheetTileDimensions.x;
		}
		else
		{
			// logic for going from animation frame 0, 1, 2, ... n-1, n, n-1, ... 2, 1, 0
			if (currentSpriteTile.x >= spriteSheetTileDimensions.x - 1)
				isFrameDirectionForward = false;
			else if (currentSpriteTile.x == 0)	// unsigned int < 0 doesnt exist because of integer underflow (must be == 0)
				isFrameDirectionForward = true;

			if (isFrameDirectionForward)
				++currentSpriteTile.x;
			else
				--currentSpriteTile.x;
		}
	}
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
	else
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

	if (this->isAnimated)
	{
		this->updateAnimationState(dir, isMoving);
		this->updateFrame(dt);
		this->updateCrop();
	}
}

void AnimatedSprite::setAnimationState(const AnimationState state)
{
	switch (state)
	{
	case AnimationState::IDLE_UP:		currentSpriteTile.y = 0;	break;
	case AnimationState::IDLE_LEFT:		currentSpriteTile.y = 1;	break;
	case AnimationState::IDLE_RIGHT:	currentSpriteTile.y = 2;	break;
	case AnimationState::IDLE_DOWN:		currentSpriteTile.y = 3;	break;

	case AnimationState::MOVING_UP:		currentSpriteTile.y = 4;	break;
	case AnimationState::MOVING_LEFT:	currentSpriteTile.y = 5;	break;
	case AnimationState::MOVING_RIGHT:	currentSpriteTile.y = 6;	break;
	case AnimationState::MOVING_DOWN:	currentSpriteTile.y = 7;	break;
	}
}

void AnimatedSprite::setSpriteSheetDimensions(const sf::Vector2u dimensions) { this->spriteSheetTileDimensions = dimensions;	}
void AnimatedSprite::setKeyFrameMaxDuration(const float duration)			 { this->keyFrameMaxDuration = duration;			}
void AnimatedSprite::setIsAnimated(const bool isAnimated)					 { this->isAnimated = isAnimated;					}

const AnimationState AnimatedSprite::getAnimationState() const { return this-> animationState; }