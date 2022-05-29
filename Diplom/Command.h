#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include <map>

#include "Structure.h"


using namespace sf;

class Command : public Drawable
{
public:
	Font font;
	std::list<Text*> text;
	Text txt;

	Vector2f movePos;
	std::list <Vector2f> movePatrolPos;
	std::list<Vector2f>::iterator tpoint;

	std::list<RectangleShape> points;
	RectangleShape ppoint;

	RectangleShape mpoint;

	Texture texture;
	Sprite plusb;
	Sprite xb;

	RectangleShape box;
	RectangleShape* choice;

public:
	bool moveTarget = false;

	bool isMove = false, isMoving = false;

	bool isMine = false, mineobjinit = false;
	bool isMineIron = false, isMineStone = false;

	bool isPatrol = false;
	bool startPatrol = false;

	bool isBuild = false;
	bool bildpos = false, startbulid = false;
	std::string buildingName;

	bool isAttack = false;

	bool isDrop = false;
	bool droping = false;

	bool isPickUp = false;

	bool onPoint = true;

	int priority = 1;
	Text txtpriority;
	RectangleShape priorityBox;

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

		priorityBox.setSize(Vector2f(25, 25));
		priorityBox.setFillColor(Color(0,120,0,100));

		ppoint.setSize(Vector2f(5, 5));
		ppoint.setOrigin(2.5, 2.5);
		ppoint.setFillColor(Color::Yellow);

		mpoint.setSize(Vector2f(5, 5));
		mpoint.setOrigin(2.5, 2.5);


		texture.loadFromFile("data/img/icons/icons.png");
		plusb.setTexture(texture);
		plusb.setTextureRect(IntRect(0, 0, 25, 25));
		xb.setTexture(texture);
		xb.setTextureRect(IntRect(25, 0, 25, 25));

		choice = new RectangleShape;
	};

	void create(Vector2f mousePos, bool& isPressed);

	void falcom();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
#endif COMMAND_H
