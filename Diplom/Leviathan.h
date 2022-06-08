#pragma once

#include "livingEntity.h"
#include "Enemy.h"
#include "Bots.h"

class Leviathan : public livingEntity
{
public:
	bool attack = false;
	Vector2f attBotPos;

private:
	bool action = false;
	bool wait = false;

	int random = 0;
	int waitingTime = 0;

	Clock cl;
	Time t;

	Clock clSpawn;
	Time tSpawn;

public:
	Leviathan(int x = 0, int y = 0);

	void update(Time deltaTime, std::list<Enemy*>& enemy, std::list<Bots*> bot);
	void move(Time deltaTime);
};