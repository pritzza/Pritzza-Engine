#include "Window.h"

Window::Window(const std::string& windowName, const unsigned int w, const unsigned int h, const unsigned int s)
	:
	window(sf::VideoMode(w* s, h* s), windowName),
	WIDTH{ w },
	HEIGHT{ h },
	SCALE{ s }
{}

void Window::update()
{
	sf::Event event;

	if (this->window.pollEvent(event))
		switch (event.type)
		{
		case sf::Event::Closed:			this->window.close();			break;
		case sf::Event::GainedFocus:	this->focused = true;	break;
		case sf::Event::LostFocus:		this->focused = false;	break;
		}
}

void Window::beginDraw()
{
	this->window.clear(sf::Color(1, 69, 13));
}

void Window::endDraw()
{
	this->window.display();
}

void Window::draw(const sf::Drawable& drawable)
{
	this->window.draw(drawable);
}

sf::RenderWindow& Window::getWindow() { return this->window; }

const bool Window::isOpen() const { return window.isOpen(); }
const bool Window::isFocused() const { return this->focused; }

const unsigned int Window::getWidth()  const	{ return WIDTH;  }
const unsigned int Window::getHeight() const	{ return HEIGHT; }
const unsigned int Window::getScale()  const	{ return SCALE;  }
