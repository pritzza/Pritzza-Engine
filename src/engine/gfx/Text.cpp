#include "Text.h"

void Text::init(const sf::Font& font, const TextType tt, const std::string& string, const sf::Vector2f& pos, const int size, const sf::Color color)
{
	this->setFont(font);

	this->setPosition(pos);
	this->setString(string);
	this->setCharacterSize(size);
	this->setFillColor(color);
}

void Text::initAppearance(const int size, const sf::Color fillColor, const sf::Color borderColor, const int borderThickness)
{
	this->setCharacterSize(size);
	this->setFillColor(fillColor);
}

void Text::update()
{
	switch (this->textType)
	{
	case TextType::FOLLOWING:

		break;
	case TextType::STATIC:

		break;
	case TextType::HUD:

		break;
	}
}
