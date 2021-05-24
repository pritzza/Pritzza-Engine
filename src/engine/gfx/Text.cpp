#include "Text.h"

void Text::init(const sf::Font& font, const std::string& string, const sf::Vector2f& pos, const int size, const sf::Color color)
{
	this->text.setFont(font);

	this->text.setPosition(pos);
	this->text.setString(string);
	this->text.setCharacterSize(size);
	this->text.setFillColor(color);
}

void Text::setText(const std::string& text)
{
	this->text.setString(text);
}

void Text::setPos(const sf::Vector2f& pos)
{
	this->text.setPosition(pos);
}

const sf::Text& Text::getSFText() const
{
	return this->text;
}
