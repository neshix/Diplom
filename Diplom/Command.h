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

	RectangleShape box;
	RectangleShape deldox;

	bool moveTarget = false;

	bool isMove = false, isMoving = false;

	bool isMine = false, mineobjinit = false;
	bool isMineIron = false, isMineTree = false, isMineStone = false;

	bool isPatrol = false;
	bool startPatrol = false;

	bool isBuild = false;

	bool isAttack = false;

	bool isDrop = false;
	bool isMaterials = false, isWeapon = false;
	bool isPickUp = false;

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

	void create(Vector2f mousePos, bool& isPressed, std::list<Structure*>& str);

	void falcom();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
#endif COMMAND_H
