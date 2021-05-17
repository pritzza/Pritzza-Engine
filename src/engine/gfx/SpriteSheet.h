#pragma once

#include "SFML/Graphics.hpp"

// class to help organize sprite
/*

should:
store sprite sheet dimensions
how many frames each horizontal animation has
the length of each keyframe

maybe?:
store hitbox for each sprite


*/
class SpriteSheet
{
private:
	sf::Texture texture;

	const sf::Vector2u spriteDimensions;
	const sf::Vector2u spriteSheetDimenions;
	const std::vector<int> keyFrameDurations;
};