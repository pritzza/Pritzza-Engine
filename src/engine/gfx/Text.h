#pragma once

#include <SFML/Graphics.hpp>

class GameObject;

enum class TextType
{
	HUD,		// doesnt move, un effected by camera movement/zoom
	STATIC,		// doesnt move, but is effected by camera movement/zoom
	FOLLOWING	// follows some game object and is effected by camera zomm
};

class Text : public sf::Text
{
private:
	TextType textType;

	const GameObject* followingTarget{ nullptr };

	sf::Vector2i anchor{};

public:
	void init(
		const sf::Font& font, 
		const TextType tt, 
		const std::string& string = "", 
		const sf::Vector2f& pos = {0,0}, 
		const int size = 10, 
		const sf::Color color = { 0,0,0 }
	);
	void initAppearance(
		const int size, 
		const sf::Color color = { 0,0,0 }, 
		const sf::Color outline = {0,0,0}, 
		const int borderThickness = 0
	);

	virtual void update();

	void setFollowingTarget(const GameObject* const target);
	void setAnchor(const sf::Vector2i anchor);
};