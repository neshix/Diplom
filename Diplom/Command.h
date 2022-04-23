#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include <map>


using namespace sf;

class Command : public Drawable
{
public:
	Font font;
	std::list<Text*> text;
	Text txt;

	Vector2f movePos;

	RectangleShape box;
	RectangleShape deldox;

	bool moveTarget = false;

	bool isMoving = false, isMove = false;

	bool isMine = false, mineobjinit = false;
	bool isMineIron = false, isMineTree = false, isMineStone = false;

	bool onPoint = true;

	int priority = 1;
	Text txtpriority;

public:
	Command(Font f) 
	{
		font = f;
		txt.setFont(font);
		txt.setCharacterSize(15);

		txtpriority.setFont(font);
		txtpriority.setCharacterSize(15);
		txtpriority.setString(std::to_string(priority));

		box.setSize(Vector2f(200, 50));
		box.setOutlineThickness(2);
		box.setOutlineColor(Color::White);
		box.setFillColor(Color(255,50,50,255));

		deldox.setSize(Vector2f(20, 20));
		deldox.setFillColor(Color(255, 255, 255, 255));
	};

	void create(Vector2f mousePos, bool& isPressed);

	void falcom();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
#endif COMMAND_H
