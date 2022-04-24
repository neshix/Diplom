#ifndef BOTS_H
#define BOTS_H

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Entity.h"
#include "Command.h"
#include "MineObj.h"

class Bots : public Entity
{
public:
	std::list<Command*> command;
	MineObj* obj;

	int maxPriority = 0;

	int iventory = 0;
	int capacity = 0;

	bool finish = false;
	bool selected = false;
	bool *point;

private:
	std::list<Vector2f>::iterator tpoint;
	Vector2f p;

	Clock cl;
	Time t;

	Font f;
public://надо найти куда запихать в drawble
	RectangleShape info;
	Text infoTxt;

public:
	Bots(int x = 500, int y = 500) :Entity()
	{
		_shape.setFillColor(Color::Blue);
		_shape.setOutlineColor(Color::White);
		setPosition(x, y);

		info.setSize(Vector2f(200, 200));
		info.setFillColor(Color(128, 128, 128, 255));

		if (!f.loadFromFile("fons/calibri.ttf")) std::cout << "ne naideno";
		infoTxt.setFont(f);
		infoTxt.setCharacterSize(15);
	};

	void AddCommand(Font font);
	void delCommand(Vector2f mpos, bool& press);
	void setPosCommand(Vector2f pos);
	void setInfoTXT();

	void realization(Vector2f t, std::list<MineObj*> en);

	void moveTo(Time deltaTime);
};
#endif BOTS_H