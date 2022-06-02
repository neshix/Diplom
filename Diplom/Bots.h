#ifndef BOTS_H
#define BOTS_H

#include <SFML/Graphics.hpp>

#include "livingEntity.h"
#include "Command.h"
#include "MineObj.h"
#include "Structure.h"
#include "Storage.h"
#include "Enemy.h"
#include "Bullet.h"

class Bots : public livingEntity
{
public:
	std::list<Command*> command;
	MineObj* obj;

	int maxPriority = 0;

	float smallerDistance = 10000;

	int iventory = 2525;
	int capacity = 0;

	int energy = 100;
	int en = 0;

	bool finish = false;
	bool selected = false;
	bool build = false;
	bool *point;

	bool fullInv = false;
	bool emptyInv = false;
	bool enemyDetected = false;
	bool noEnergy = false;

private:
	Vector2f p;

	Clock cl;
	Clock enrgycl;
	Time t;

	Clock edcl;
	Time edt;

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

		capacity = (iventory % 100) + ((iventory / 100) % 100);

		if (!f.loadFromFile("fons/calibri.ttf")) std::cout << "ne naideno";
		infoTxt.setFont(f);
		infoTxt.setCharacterSize(15);

		reviewBox.setFillColor(Color(0, 0, 255, 30));
		reviewBox.setSize(Vector2f(400, 400));
		reviewBox.setOrigin(Vector2f(400 / 2, 400 / 2));
	};

	void AddCommand(Font font);
	void delCommand(Vector2f mpos, bool& press);
	void setPosCommand(Vector2f pos);
	void setInfoTXT();

	void update(Vector2f t, std::list<MineObj*>& mine, std::list<Structure*>& str, Storage& stor, std::list<Enemy*>& en, std::list<Bullet*>& bul);
	void statup(std::list<Enemy*>& enemy);

	void moveTo(Time deltaTime);
};
#endif BOTS_H