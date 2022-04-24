#ifndef CONSOLE_H
#define CONSOLE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Console : public sf::Drawable
{
public:
	RectangleShape consol;
	RectangleShape bAdd;

public:
	Console();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(consol, states);
		target.draw(bAdd, states);
	};
};
#endif CONSOLE_H