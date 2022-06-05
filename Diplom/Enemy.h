#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Entity.h"


class Enemy : public livingEntity
{
private:
	bool action = false;
	bool wait = false;

	bool follow = false;
	bool followE = false;
	bool followL = false;
	int who = 0;

	int random = 0;
	int waitingTime = 0;

	Clock cl;
	Time t;

	Leviathan* lev;
	Enemy* ene;

public:
	Enemy(Vector2f pos);
	void update(Time deltaTime, std::list<Enemy*>& enemy, std::list<Leviathan*> Leviathan, std::list<Bots*> bot);
	void move(Time deltaTime);

};
#endif ENEMY_H