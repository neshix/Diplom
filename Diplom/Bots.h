#ifndef BOTS_H
#define BOTS_H

#include <SFML/Graphics.hpp>

#include "livingEntity.h"
#include "Command.h"
#include "MineObj.h"
#include "Structure.h"
#include "Storage.h"

class Bots : public livingEntity
{
public:
	std::list<Command*> command;
	MineObj* obj;

	int maxPriority = 0;

	int iventory = 121433;
	int capacity = 0;

	bool finish = false;
	bool selected = false;
	bool build = false;
	bool *point;

private:
	Vector2f p;

	Clock cl;
	Time t;

public://надо найти куда запихать в drawble
	Font f;
	RectangleShape info;
	Text infoTxt;

public:
	Bots(int x = 500, int y = 500) :livingEntity("data/img/bot.png")
	{
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

	void update(Vector2f t, std::list<MineObj*>& mine, std::list<Structure*>& str, Storage& stor);

	void moveTo(Time deltaTime);
};
#endif BOTS_H