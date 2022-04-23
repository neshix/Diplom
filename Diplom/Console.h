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
	Console()
	{
		consol.setSize(Vector2f(200, 800));
		consol.setPosition(1400, 0);
		consol.setFillColor(Color::Red);

		bAdd.setSize(Vector2f(50, 50));
		bAdd.setPosition(1400, 0);
		bAdd.setFillColor(Color(255,100,0,255));
	};

public:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(consol, states);
		target.draw(bAdd, states);
	};
};
#endif CONSOLE_H