#pragma once

#include <SFML/Graphics.hpp>

enum class TextType
{
	HUD,		// doesnt move, un effected by camera movement/zoom
	STATIC,		// doesnt move, but is effected by camera movement/zoom
	FOLLOWING	// follows some game object and is effected by camera zomm
};

class Text
{
private:
	sf::Text text;

public:
	void init(const sf::Font& font, const std::string& string = "", const sf::Vector2f& pos = {0,0}, const int size = 10, const sf::Color color = { 0,0,0 });

	void setText(const std::string& text);
	void setPos(const sf::Vector2f& pos);

	const sf::Text& getSFText() const;
};