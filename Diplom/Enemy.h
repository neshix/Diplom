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

	int random = 0;
	int waitingTime = 0;

	Clock cl;
	Time t;

public:
	Enemy(Vector2f pos);
	void update(Time deltaTime, std::list<Enemy*>& enemy);
	void move(Time deltaTime);

};
#endif ENEMY_H